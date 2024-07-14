#ifndef XPFCORE_H
#define XPFCORE_H

#include "IXPFPlugin.h"
#include "IXPFPluginHelper.h"
#include <QMap>
#include <QLibrary>
#include <QVariant>
#include <QLinkedList>
#include <QDomElement>
#include <QLocalServer>

#define STR_XPF_APPNAME             "AppName"
#define STR_XPF_MULTISTART_ENABLE   "MultiStart"

class XPFCore
{
public:
    XPFCore();
    virtual ~XPFCore();
    bool load();
    /**
     * @brief showScreens 显示所有屏幕界面
     */
    void showScreens();

private:

    /**
     * @brief isAlreadyRunning 检查是否重复运行
     * @return 是否重复运行
     */
    bool isAlreadyRunning();

    /**
     * @brief parseScreenXml 解析屏幕相关配置
     * @param em 配置元素
     * @return 配置是否有错误
     */
    bool parseScreenXml(const QDomElement &em);

    /**
     * @brief loadPlugins 加载插件
     */
    void loadPlugins();
private:
    // 应用配置
    QVariantMap m_Config;
    // 所有的插件
    QMap<QString, IXPFPlugin*> m_Plugins;
    // XPF Helper
    IXPFPluginHelper *m_XPFHelper;

    QLocalServer *m_LocalServer;
};

#endif // XPFCORE_H
