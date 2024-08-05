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

    virtual void initPlugin(IXPFPluginHelper* pluginHelper) = 0;

    virtual void initAfterPlugin() = 0;

    /**
     * @brief getWidget 获取窗体控件
     * @param WID 窗体ID
     * @return 窗体控件指针
     */
    virtual QWidget* getWidget(const QString& WID) = 0;

    /**
     * @brief release 插件释放
     */
    virtual void release() = 0;

    virtual void onMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) = 0;
};

#define IXPFPlugin_IID "com.xpf.IXPFPlugin"
Q_DECLARE_INTERFACE(IXPFPlugin, IXPFPlugin_IID)

#endif
