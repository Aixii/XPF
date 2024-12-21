#include "MessageSenderPrivate.h"
#include "XPFPluginHelperImplPrivate.h"
#include <IXPFPlugin>

#include <QDebug>

using namespace XPF;

MessageSenderPrivate::MessageSenderPrivate(QObject* parent)
    : QObject(parent)
    , m_Helper(nullptr) {
}

void MessageSenderPrivate::bindHelper(XPFPluginHelperImplPrivate* helper) {
    m_Helper = helper;
}

void MessageSenderPrivate::slotSendAsyncMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    if (m_Helper == nullptr) {
        return;
    }

    if (m_Helper->m_MsgSubscribes.contains(topic) && m_Helper->m_MsgSubscribes[topic].contains(msgid)) {
        std::list<IXPFPlugin*>& list = m_Helper->m_MsgSubscribes[topic][msgid];
        for (IXPFPlugin* plugin : list) {
            plugin->onMessage(topic, msgid, param, sender);
        }
    }
}
