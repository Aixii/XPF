#ifndef MESSAGESENDERPRIVATE_H
#define MESSAGESENDERPRIVATE_H

#include "IXPFPlugin.h"
#include <QObject>

namespace XPF {
class XPFPluginHelperImplPrivate;

class MessageSenderPrivate : public QObject
{
    Q_OBJECT
public:
    explicit MessageSenderPrivate(QObject *parent = nullptr);
    void bindHelper(XPFPluginHelperImplPrivate *helper);

public slots:
    void slotSendAsyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender);

private:
    XPFPluginHelperImplPrivate *m_Helper;
};

}

#endif // MESSAGESENDERPRIVATE_H
