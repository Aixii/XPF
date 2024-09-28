#pragma once

#include "IXPFPlugin.h"
#include <QObject>

class XPFLoginPlugin
    : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFLoginPlugin();
    ~XPFLoginPlugin();

    // IXPFPlugin interface
public:
    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override;
    void release() override;
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;

    QWidget* getWidget(const QString& WID) override;
    QString  getPluginName();
};
