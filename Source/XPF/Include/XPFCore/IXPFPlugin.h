#ifndef IXPFPLUGIN_H
#define IXPFPLUGIN_H

#include <QObject>

class IXPFPluginHelper;

class IXPFPlugin {
public:
    IXPFPlugin() {
    }
    virtual ~IXPFPlugin() {
    }

    /**
     * @brief getWidget 获取窗体控件
     * @param WID 窗体ID
     * @return 窗体控件指针
     */
    virtual QWidget* getWidget(const QString& WID) = 0;

    /**
     * @brief getPluginName 获取插件名
     * @return
     */
    virtual QString getPluginName() = 0;

    /**
     * @brief initPlugin 初始化插件
     * @param pluginHelper 插件助手
     */
    virtual void initPlugin(IXPFPluginHelper* pluginHelper) = 0;

    /**
     * @brief initAfterPlugin 初始化之后
     */
    virtual void initAfterPlugin() = 0;

    /**
     * @brief release 插件释放
     */
    virtual void release() = 0;

    /**
     * @brief onMessage 消息处理
     * @param topic 主题
     * @param msgid 消息ID
     * @param param 参数
     * @param sender 发送者
     */
    virtual void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) = 0;

    /**
     * @brief onMessage 消息处理
     * @param topic 主题
     * @param msgid 消息ID
     * @param param 参数
     * @param sender 发送者
     */
    virtual void onSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
        Q_UNUSED(topic)
        Q_UNUSED(msgid)
        Q_UNUSED(param)
        Q_UNUSED(sender)
    }
};

#define IXPFPlugin_IID "com.xpf.IXPFPlugin"
Q_DECLARE_INTERFACE(IXPFPlugin, IXPFPlugin_IID)

#endif
