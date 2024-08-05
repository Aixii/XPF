#include "XPFPluginHelperImplPrivate.h"
#include "MessageSenderPrivate.h"
#include "XPFCore.h"
#include "XPFDef.h"
#include <QFileInfo>
#include <QString>
#include <QThread>
#include <QWidget>

extern XPFCore* xpf_core;

using namespace XPF;

XPFPluginHelperImplPrivate::XPFPluginHelperImplPrivate(QObject* parent)
    : QObject(parent) {
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

void XPFPluginHelperImplPrivate::subMessage(IXPFPlugin* plugin, uint32_t msgid) {
    if (m_MsgSubscribes[msgid].contains(plugin)) {
        return;
    }

    m_MsgSubscribes[msgid].push_back(plugin);
}

void XPFPluginHelperImplPrivate::unsubMessage(IXPFPlugin* plugin, uint32_t msgid) {
    if (m_MsgSubscribes.contains(msgid)) {
        QLinkedList<IXPFPlugin*>& list = m_MsgSubscribes[msgid];
        if (list.contains(plugin)) {
            list.removeOne(plugin);
        }
    }
}

void XPFPluginHelperImplPrivate::sendMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    emit sigSendAsyncMessage(msgid, param, sender);
}

void XPFPluginHelperImplPrivate::sendSyncMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    if (m_MsgSubscribes.contains(msgid)) {
        QLinkedList<IXPFPlugin*>& list = m_MsgSubscribes[msgid];
        for (IXPFPlugin* plugin : list) {
            plugin->onMessage(msgid, param, sender);
        }
    }

    if (msgid == XPF_MSG_ID_QUIT_APP) {
        xpf_core->quitApp();
    }
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
