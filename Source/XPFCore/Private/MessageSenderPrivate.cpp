#include "MessageSenderPrivate.h"
#include "XPFPluginHelperImplPrivate.h"

using namespace XPF;

MessageSenderPrivate::MessageSenderPrivate(QObject *parent)
    : QObject(parent)
    , m_Helper(nullptr)
{

}

void MessageSenderPrivate::bindHelper(XPFPluginHelperImplPrivate *helper)
{
    m_Helper = helper;
}

void MessageSenderPrivate::slotSendAsyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender)
{
    if(m_Helper == nullptr)
    {
        return;
    }
    if(m_Helper->m_MsgSubscribes.contains(msgid))
    {
        QLinkedList<IXPFPlugin*> &list = m_Helper->m_MsgSubscribes[msgid];
        for(IXPFPlugin *plugin : list)
        {
            plugin->onMessage(msgid, param, sender);
        }
    }
}
