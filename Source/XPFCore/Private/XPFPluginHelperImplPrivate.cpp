#include "XPFPluginHelperImplPrivate.h"
#include "MessageSenderPrivate.h"
#include "XPFCore.h"
#include "XPFCoreDef.h"
#include "XPFTopicDef.h"
#include <QFileInfo>
#include <QMutexLocker>
#include <QString>
#include <QThread>
#include <QWidget>

extern XPFCore* xpf_core;

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

QString XPFPluginHelperImplPrivate::getXPFBinDir() {
    QFileInfo file(".");
    QString   path = file.absoluteFilePath();
    return path;
}

QString XPFPluginHelperImplPrivate::getXPFBinConfigDir() {
    QFileInfo file("./XPFConfig");
    QString   path = file.absoluteFilePath();
    return path;
}

void XPFPluginHelperImplPrivate::subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    if (topic.isEmpty()) {
        qWarning() << "无法订阅空的主题";
        return;
    }
    if (m_MsgSubscribes[topic][msgid].contains(plugin)) {
        qWarning() << QString("重复订阅主题消息， %0 subscribes %1:%2").arg(plugin->getPluginName()).arg(topic).arg(QString::number(msgid));
        return;
    }

    m_MsgSubscribes[topic][msgid].push_back(plugin);
}

void XPFPluginHelperImplPrivate::unsubMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    if (m_MsgSubscribes.contains(topic) && m_MsgSubscribes[topic].contains(msgid)) {
        QLinkedList<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];
        if (list.contains(plugin)) {
            list.removeOne(plugin);
        }
    }
}

void XPFPluginHelperImplPrivate::sendMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    emit sigSendAsyncMessage(topic, msgid, param, sender);
}

void XPFPluginHelperImplPrivate::sendSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    if (m_MsgSubscribes.contains(topic) && m_MsgSubscribes[topic].contains(msgid)) {
        QLinkedList<IXPFPlugin*>& list = m_MsgSubscribes[topic][msgid];
        for (IXPFPlugin* plugin : list) {
            plugin->onMessage(topic, msgid, param, sender);
        }
    }

    if (topic == TOPIC_Core && msgid == XPF_Core::MSG_ID_QUIT_APP) {
        xpf_core->quitApp();
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
    if (xpf_core != nullptr) {
        IXPFPlugin* plugin = xpf_core->getPlugin(plugin_name);
        if (plugin != nullptr) {
            widget = plugin->getWidget(plugin_winid);
        }
    }
    return widget;
}

QList<QWidget*> XPFPluginHelperImplPrivate::getXPFScreenWidgets() {
    return m_ScreenWidgets.values();
}
