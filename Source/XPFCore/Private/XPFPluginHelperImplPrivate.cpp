#include "XPFPluginHelperImplPrivate.h"
#include "MessageSenderPrivate.h"
#include <QFileInfo>
#include <QString>
#include <QThread>

using namespace XPF;

XPFPluginHelperImplPrivate::XPFPluginHelperImplPrivate(QObject *parent)
    : QObject(parent)
{
    m_MsgSendThread = new QThread(this);
    m_MsgSender = new MessageSenderPrivate(this);

    m_MsgSender->bindHelper(this);

    QObject::connect(this, &XPFPluginHelperImplPrivate::sigSendAsyncMessage,
                     m_MsgSender, &MessageSenderPrivate::slotSendAsyncMessage);

    m_MsgSendThread->start();
}

XPFPluginHelperImplPrivate::~XPFPluginHelperImplPrivate()
{
    m_MsgSendThread->terminate();
    delete m_MsgSendThread;

    delete m_MsgSender;
}

QString XPFPluginHelperImplPrivate::getXPFBinDir()
{
    QFileInfo file(".");
    QString path = file.absoluteFilePath();
    return path;
}

QString XPFPluginHelperImplPrivate::getXPFBinConfigDir()
{
    QFileInfo file("./XPFConfig");
    QString path = file.absoluteFilePath();
    return path;
}

void XPFPluginHelperImplPrivate::subMessage(IXPFPlugin *plugin, uint32_t msgid)
{
    if(m_MsgSubscribes[msgid].contains(plugin))
    {
        return;
    }

    m_MsgSubscribes[msgid].push_back(plugin);
}

void XPFPluginHelperImplPrivate::unsubMessage(IXPFPlugin *plugin, uint32_t msgid)
{
    if(m_MsgSubscribes.contains(msgid))
    {
        QLinkedList<IXPFPlugin*> &list = m_MsgSubscribes[msgid];
        if(list.contains(plugin))
        {
            list.removeOne(plugin);
        }
    }
}

void XPFPluginHelperImplPrivate::sendMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender)
{
    emit sigSendAsyncMessage(msgid, param, sender);
}

void XPFPluginHelperImplPrivate::sendSyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender)
{
    if(m_MsgSubscribes.contains(msgid))
    {
        QLinkedList<IXPFPlugin*> &list = m_MsgSubscribes[msgid];
        for(IXPFPlugin *plugin : list)
        {
            plugin->onMessage(msgid, param, sender);
        }
    }
}

QWidget *XPFPluginHelperImplPrivate::getXPFScreenWidget(int screenID)
{
    return m_ScreenWidgets.value(screenID, nullptr);
}
