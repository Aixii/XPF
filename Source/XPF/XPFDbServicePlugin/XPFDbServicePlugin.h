#pragma once

#include <IXPFDbServiceFactory>
#include <IXPFPlugin>
#include <QObject>

class XPFDbService4SqlitePlugin
    : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFDbService4SqlitePlugin();
    ~XPFDbService4SqlitePlugin();

    // IXPFPlugin interface
public:
    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override;
    void release() override;
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;

    QWidget* getWidget(const QString& WID) override;
    QString  getPluginName() override;

private:
    IXPFDbServiceFactory* m_Factory;
};
