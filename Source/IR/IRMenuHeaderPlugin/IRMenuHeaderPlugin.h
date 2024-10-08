#pragma once

#include "IXPFPlugin.h"
#include "Widgets/IR_MenuHeaderWgt.h"
#include <QObject>

class IRMenuHeaderPlugin
    : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    IRMenuHeaderPlugin();
    ~IRMenuHeaderPlugin();

    // IXPFPlugin interface
public:
    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override;
    void release() override;
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;

    QWidget* getWidget(const QString& WID) override;
    QString  getPluginName();

private:
    IR_MenuHeaderWgt* m_MenuHeaderWgt;
};
