#ifndef IXPFPLUGINHELPER_H
#define IXPFPLUGINHELPER_H

#include <QString>
#include <QVariant>

class IXPFPlugin;
class IXPFService;

class IXPFPluginHelper {
public:
    IXPFPluginHelper() { }
    virtual ~IXPFPluginHelper() { }

    // clang-format off
    /**
     * @brief subMessage 订阅消息
     * @param plugin 插件
     * @param topic 主题
     * @param msgid 消息 ID
     */
    virtual void subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) = 0;

    /**
     * @brief unsubMessage 取消订阅消息
     * @param plugin 插件
     * @param topic 主题
     * @param msgid 消息 ID
     */
    virtual void unsubMessage(IXPFPlugin* plugin,
                              const QString& topic = QString(),
                              uint32_t msgid = 0) = 0;

    /**
     * @brief sendMessage 发送异步消息
     * @param topic 主题
     * @param msgid 消息ID
     * @param param 参数
     * @param sender 发送者
     */
    virtual void sendMessage(const QString& topic,
                             uint32_t msgid,
                             const QVariant& param = QVariant(),
                             IXPFPlugin* sender = nullptr) = 0;

    /**
     * @brief sendSyncMessage 发送同步消息
     * @param topic 主题
     * @param msgid 消息ID
     * @param param 参数
     * @param sender 发送者
     */
    virtual void sendSyncMessage(const QString& topic,
                                 uint32_t msgid,
                                 const QVariant& param = QVariant(),
                                 IXPFPlugin* sender = nullptr) = 0;


    /**
     * @brief registerService 注册服务对象
     * @param name 服务名
     * @param servicePtr 对象指针
     * @return
     */
    virtual bool registerService(const QString& name, IXPFService* servicePtr) = 0;

    /**
     * @brief unregisterService 注销服务对象
     * @param name 服务名称
     */
    virtual void unregisterService(const QString& name) = 0;

    /**
     * @brief registerPlugin 注册插件
     * @param plugin 插件
     * @param who 谁注册的（用来限制调用者）
     * @return
     */
    virtual bool registerPlugin(IXPFPlugin *plugin, void *who) = 0;

    /**
     * @brief unregisterPlugin 注销插件
     * @param plugin 插件
     * @param who 谁注销的（用来限制调用者）
     */
    virtual void unregisterPlugin(IXPFPlugin *plugin, void *who) = 0;

    /**
     * @brief getService 获取服务对象
     * @param iid 服务接口对象id
     * @return
     */
    virtual IXPFService* getService(const QString& iid) = 0;

    /**
     * @brief getXPFScreenWidget 获取屏幕窗口
     * @param screenID 屏幕ID
     * @return
     */
    virtual QWidget* getXPFScreenWidget(int screenID) = 0;

    /**
     * @brief getXPFWidgetById 获取Widget
     * @param screenID 所属屏幕ID
     * @param id WidgetID
     * @return
     */
    virtual QWidget* getXPFWidgetById(int screenID, const QString& id) = 0;

    /**
     * @brief getXPFWidgetByPlugin 获取插件窗口
     * @param plugin_name 插件名字
     * @param plugin_winid 窗口ID
     * @return
     */
    virtual QWidget* getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) = 0;

    /**
     * @brief getXPFScreenWidgets 获取所有屏幕窗口
     * @return
     */
    virtual QList<QWidget*> getXPFScreenWidgets() = 0;
    // clang-format on
};

#endif // IXPFPLUGINHELPER_H
