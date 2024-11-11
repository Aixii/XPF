#ifndef XPFPLUGINHELPERIMPLPRIVATE_H
#define XPFPLUGINHELPERIMPLPRIVATE_H

#include "MessageSenderPrivate.h"
#include "XPFPluginHelperImpl.h"
#include <IXPFPlugin>
#include <IXPFPluginHelper>
#include <QMap>
#include <QMutex>
#include <QObject>
#include <list>

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
    void sigSendAsyncMessage(const QString&  topic,
                             uint32_t        msgid,
                             const QVariant& param,
                             IXPFPlugin*     sender);

    // IXPFPluginHelper interface
public:
    void subMessage(IXPFPlugin*    plugin,
                    const QString& topic,
                    uint32_t       msgid = 0) override;

    void unsubMessage(IXPFPlugin*    plugin,
                      const QString& topic,
                      uint32_t       msgid = 0) override;

    void sendMessage(const QString&  topic,
                     uint32_t        msgid,
                     const QVariant& param  = QVariant(),
                     IXPFPlugin*     sender = nullptr) override;

    void sendSyncMessage(const QString&  topic,
                         uint32_t        msgid,
                         const QVariant& param  = QVariant(),
                         IXPFPlugin*     sender = nullptr) override;

    bool registerService(const QString& name, IXPFService* servicePtr) override;

    IXPFService* getService(const QString& name) override;

    QWidget* getXPFScreenWidget(int screenID) override;
    QWidget* getXPFWidgetById(int screenID, const QString& id) override;
    QWidget* getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) override;

    QList<QWidget*> getXPFScreenWidgets() override;

    void unregisterService(const QString& name) override;
    bool registerPlugin(IXPFPlugin* plugin, void* who) override;
    void unregisterPlugin(IXPFPlugin* plugin, void* who) override;

private:
    // 消息订阅关系
    QMap<QString, QMap<uint32_t, std::list<IXPFPlugin*>>> m_MsgSubscribes;
    //    QMap<uint32_t, QLinkedList<IXPFPlugin*>> m_MsgSubscribes;
    // 消息发送线程
    QThread* m_MsgSendThread;
    // 消息发送者
    XPF::MessageSenderPrivate* m_MsgSender;
    // 所有屏幕窗口
    QMap<int, QWidget*> m_ScreenWidgets;

    QMap<QString, IXPFService*> m_Services;

    QMap<QString, IXPFPlugin*> m_Plugins;

    QMutex* m_ServicesMutex;
};

}

#endif // XPFPLUGINHELPERIMPLPRIVATE_H
