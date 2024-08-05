#ifndef XPFCORE_H
#define XPFCORE_H

#include "IXPFPlugin.h"
#include "IXPFPluginHelper.h"
#include <QDomElement>
#include <QLibrary>
#include <QLinkedList>
#include <QLocalServer>
#include <QMap>
#include <QPluginLoader>
#include <QSystemTrayIcon>
#include <QVariant>

#define STR_XPF_APPNAME "AppName"
#define STR_XPF_MULTISTART_ENABLE "MultiStart"

class XPFCore : public QObject {
    Q_OBJECT
public:
    explicit XPFCore(QObject* parent = nullptr);
    virtual ~XPFCore();

    // 显示所有屏幕界面
    void showScreens();
    void quitApp();

    // 初始化
    bool initialize();

    IXPFPlugin* getPlugin(const QString& name);

signals:
    void sigQuitApp();

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
    bool parseScreenXml(const QDomElement& em);

    /**
     * @brief loadPlugins 加载插件
     */
    void loadPlugins();

    // 应用程序启动加载
    bool load(const QString& fileName);

    void reloadPlugin(const QString& pluginName);
    void unloadPlugin(const QString& pluginName);

private:
    // 应用配置
    QVariantMap m_Config;
    // 所有的插件
    QMap<QString, IXPFPlugin*> m_Plugins;
    // 插件加载器
    QMap<QString, QPluginLoader*> m_PluginLoaders;
    // XPF Helper
    IXPFPluginHelper* m_XPFHelper;

    QLocalServer* m_LocalServer;

    QSystemTrayIcon* m_TrayIcon;
};

#endif // XPFCORE_H
