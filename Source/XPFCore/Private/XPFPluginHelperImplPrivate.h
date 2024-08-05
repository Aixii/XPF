#ifndef XPFPLUGINHELPERIMPLPRIVATE_H
#define XPFPLUGINHELPERIMPLPRIVATE_H

#include "IXPFPlugin.h"
#include "IXPFPluginHelper.h"
#include "MessageSenderPrivate.h"
#include "XPFPluginHelperImpl.h"
#include <QLinkedList>
#include <QMap>
#include <QObject>

namespace XPF {

class XPFPluginHelperImplPrivate
    : public QObject
    , public IXPFPluginHelper {
    Q_OBJECT
public:
    explicit XPFPluginHelperImplPrivate(QObject* parent = nullptr);
    ~XPFPluginHelperImplPrivate();

    friend class MessageSenderPrivate;
    friend void XPFPluginHelperImpl::setXPFScreenWidget(int screenID, QWidget* widget);

signals:
    // 发送异步消息
    void sigSendAsyncMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender);

    // IXPFPluginHelper interface
public:
    QString getXPFBinDir() override;
    QString getXPFBinConfigDir() override;

    void subMessage(IXPFPlugin* plugin, uint32_t msgid) override;
    void unsubMessage(IXPFPlugin* plugin, uint32_t msgid) override;
    void sendMessage(uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr) override;
    void sendSyncMessage(uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr) override;

    QWidget* getXPFScreenWidget(int screenID) override;
    QWidget* getXPFWidgetById(int screenID, const QString& id) override;
    QWidget* getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) override;

    QList<QWidget*> getXPFScreenWidgets() override;

private:
    // 消息订阅关系
    QMap<uint32_t, QLinkedList<IXPFPlugin*>> m_MsgSubscribes;
    // 消息发送线程
    QThread* m_MsgSendThread;
    // 消息发送者
    XPF::MessageSenderPrivate* m_MsgSender;
    // 所有屏幕窗口
    QMap<int, QWidget*> m_ScreenWidgets;
};

}

#endif // XPFPLUGINHELPERIMPLPRIVATE_H
