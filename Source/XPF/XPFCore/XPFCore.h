﻿#ifndef XPFCORE_H
#define XPFCORE_H

#include <IXPFPlugin>
#include <IXPFPluginHelper>
#include <QDomElement>
#include <QLibrary>
#include <QLocalServer>
#include <QMap>
#include <QPluginLoader>
#include <QSystemTrayIcon>
#include <QVariant>
#include <list>

#define STR_XPF_APPNAME           "AppName"
#define STR_XPF_MULTISTART_ENABLE "MultiStart"

class XPFCore : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
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
     * @brief loadPlugins 加载插件
     */
    bool loadPlugins();

    // 应用程序启动加载
    bool load();

    void reloadPlugin(const QString& pluginName);
    void unloadPlugin(const QString& pluginName);

    bool registerPlugin(IXPFPlugin* plugin);
    void unregisterPlugin(IXPFPlugin* plugin);

    bool registerScreen(QWidget* screen);

private:
    // 应用配置
    QVariantMap m_Config;
    // 所有的插件
    //    QMap<QString, IXPFPlugin*> m_Plugins;

    QList<IXPFPlugin*> m_PluginsSort;

    // 插件加载器
    QMap<QString, QPluginLoader*> m_PluginLoaders;

    // XPF Helper
    IXPFPluginHelper* m_XPFHelper;

    QLocalServer* m_LocalServer;

    QSystemTrayIcon* m_TrayIcon;

private slots:
    void slotTrayIconActive(QSystemTrayIcon::ActivationReason reason);

    // IXPFPlugin interface
public:
    QWidget* getWidget(const QString& WID) override {
        Q_UNUSED(WID)
        return nullptr;
    }

    QString getPluginName() override { return "xpfcore"; }

    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override { }
    void release() override { }
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;
};

#endif // XPFCORE_H
