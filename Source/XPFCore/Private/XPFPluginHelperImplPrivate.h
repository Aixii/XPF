#ifndef XPFPLUGINHELPERIMPLPRIVATE_H
#define XPFPLUGINHELPERIMPLPRIVATE_H

#include "IXPFPluginHelper.h"
#include "IXPFPlugin.h"
#include "MessageSenderPrivate.h"
#include "XPFPluginHelperImpl.h"
#include <QObject>
#include <QMap>
#include <QLinkedList>

namespace XPF {

class XPFPluginHelperImplPrivate : public QObject, public IXPFPluginHelper
{
    Q_OBJECT
public:
    explicit XPFPluginHelperImplPrivate(QObject *parent = nullptr);
    ~XPFPluginHelperImplPrivate();

    friend class MessageSenderPrivate;
    friend QList<QWidget*> XPFPluginHelperImpl::getScreens();
    friend void XPFPluginHelperImpl::setXPFScreenWidget(int screenID, QWidget *widget);

signals:
    // 发送异步消息
    void sigSendAsyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender);

    // IXPFPluginHelper interface
public:
    QString getXPFBinDir() override;
    QString getXPFBinConfigDir() override;
    void subMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void unsubMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void sendMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender) override;
    void sendSyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender) override;
    QWidget *getXPFScreenWidget(int screenID) override;

private:
    // 消息订阅
    QMap<uint32_t, QLinkedList<IXPFPlugin*>> m_MsgSubscribes;

    QThread *m_MsgSendThread;

    XPF::MessageSenderPrivate *m_MsgSender;

    QMap<int, QWidget*> m_ScreenWidgets;
};

}

#endif // XPFPLUGINHELPERIMPLPRIVATE_H
