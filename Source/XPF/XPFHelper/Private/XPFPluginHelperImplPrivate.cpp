#include "XPFPluginHelperImplPrivate.h"
#include "MessageSenderPrivate.h"
#include <QFileInfo>
#include <QMapIterator>
#include <QMutexLocker>
#include <QString>
#include <QThread>
#include <QWidget>
#include <XPFCoreTopicDef>

using namespace XPF;

XPFPluginHelperImplPrivate::XPFPluginHelperImplPrivate(QObject* parent)
    : QObject(parent) {
    m_ServicesMutex = new QMutex;

    m_MsgSendThread = new QThread(this);
    m_MsgSender     = new MessageSenderPrivate(this);

    m_MsgSender->bindHelper(this);

    QObject::connect(this, &XPFPluginHelperImplPrivate::sigSendAsyncMessage,
                     m_MsgSender, &MessageSenderPrivate::slotSendAsyncMessage);

    m_MsgSendThread->start();
}

XPFPluginHelperImplPrivate::~XPFPluginHelperImplPrivate() {
    m_MsgSendThread->terminate();
    delete m_MsgSendThread;
    delete m_MsgSender;

    delete m_ServicesMutex;
}

void XPFPluginHelperImplPrivate::subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    if (topic.isEmpty()) {
        qWarning() << tr(u8"无法订阅空的主题");
        return;
    }
    std::list<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];

    auto it = std::find(list.begin(), list.end(), plugin);

    if (it != list.end()) {
        qWarning() << QString(tr(u8"重复订阅主题消息， %0 subscribes %1:%2")).arg(plugin->getPluginName()).arg(topic).arg(QString::number(msgid));
        return;
    }

    m_MsgSubscribes[topic][msgid].push_back(plugin);
}

void XPFPluginHelperImplPrivate::unsubMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    if (topic.isEmpty()) {
        QMapIterator<QString, QMap<uint32_t, std::list<IXPFPlugin*>>> topicIter(m_MsgSubscribes);
        while (topicIter.hasNext()) {
            topicIter.next();

            const QMap<uint32_t, std::list<IXPFPlugin*>>& msgIDSubMap = topicIter.value();

            QMapIterator<uint32_t, std::list<IXPFPlugin*>> msgidIter(msgIDSubMap);
            while (msgidIter.hasNext()) {
                msgidIter.next();
                std::list<IXPFPlugin*>& list = m_MsgSubscribes[topicIter.key()][msgidIter.key()];

                list.remove(plugin);
            }
        }
    }
    else {
        if (m_MsgSubscribes.contains(topic)) {
            if (msgid == 0) {
                QMap<uint32_t, std::list<IXPFPlugin*>>& msgIDSub = m_MsgSubscribes[topic];

                QMapIterator<uint32_t, std::list<IXPFPlugin*>> msgIDIter(msgIDSub);
                while (msgIDIter.hasNext()) {
                    msgIDIter.next();
                    std::list<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];
                    list.remove(plugin);
                }
            }
            else {
                if (m_MsgSubscribes[topic].contains(msgid)) {
                    std::list<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];
                    list.remove(plugin);
                }
            }
        }
    }
}

void XPFPluginHelperImplPrivate::sendMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    emit sigSendAsyncMessage(topic, msgid, param, sender);
}

void XPFPluginHelperImplPrivate::sendSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    if (m_MsgSubscribes.contains(topic) && m_MsgSubscribes[topic].contains(msgid)) {

        std::list<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];
        for (IXPFPlugin* plugin : list) {
            plugin->onMessage(topic, msgid, param, sender);
        }
    }

    if (topic == TOPIC_XPF_CORE && msgid == XPFCore_NameSpace::MSG_ID_QUIT_APP) {
        // 退出
    }
}

bool XPFPluginHelperImplPrivate::registerService(const QString& name, IXPFService* servicePtr) {
    QMutexLocker lock(m_ServicesMutex);
    if (m_Services.contains(name) || servicePtr == nullptr) {
        return false;
    }
    m_Services[name] = servicePtr;
    return true;
}

IXPFService* XPFPluginHelperImplPrivate::getService(const QString& name) {
    QMutexLocker lock(m_ServicesMutex);
    return m_Services.value(name, nullptr);
}

QWidget* XPFPluginHelperImplPrivate::getXPFScreenWidget(int screenID) {
    return m_ScreenWidgets.value(screenID, nullptr);
}

QWidget* XPFPluginHelperImplPrivate::getXPFWidgetById(int screenID, const QString& id) {
    QWidget* sw = getXPFScreenWidget(screenID);
    if (sw == nullptr) {
        return nullptr;
    }
    QWidget* widget = sw->findChild<QWidget*>(id);
    return widget;
}

QWidget* XPFPluginHelperImplPrivate::getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) {
    QWidget* widget = nullptr;

    IXPFPlugin* plugin = m_Plugins.value(plugin_name, nullptr);
    if (plugin != nullptr) {
        widget = plugin->getWidget(plugin_winid);
    }
    return widget;
}

QList<QWidget*> XPFPluginHelperImplPrivate::getXPFScreenWidgets() {
    return m_ScreenWidgets.values();
}

void XPFPluginHelperImplPrivate::unregisterService(const QString& name) {
    m_Services.remove(name);
}

bool XPFPluginHelperImplPrivate::registerPlugin(IXPFPlugin* plugin, void* who) {
    QString name = plugin->getPluginName();
    if (name.compare("xpfcore", Qt::CaseInsensitive) == 0) {
        m_Plugins["xpfcore"] = plugin;
    }
    else {
        IXPFPlugin* core = m_Plugins.value("xpfcore", nullptr);
        if (core == nullptr || core != who) {
            return false;
        }
    }
    m_Plugins["xpfcore"] = plugin;
    return true;
}

void XPFPluginHelperImplPrivate::unregisterPlugin(IXPFPlugin* plugin, void* who) {
    QString name = plugin->getPluginName();
    if (name.compare("xpfcore", Qt::CaseInsensitive) == 0) {
        return;
    }
    else {
        IXPFPlugin* core = m_Plugins.value("xpfcore", nullptr);
        if (core == nullptr || core != who) {
            return;
        }
    }

    m_Plugins.remove(name);
}
