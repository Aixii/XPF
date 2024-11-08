#ifndef XPFUIPLUIN_H
#define XPFUIPLUIN_H

#include <IXPFPlugin>
#include "TrayIconRClickWgt.h"
#include <QObject>

class XPFTrayMenuPlugin : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    explicit XPFTrayMenuPlugin(QObject* parent = nullptr);
    ~XPFTrayMenuPlugin();

    // IXPFPlugin interface
public:
    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override;
    void release() override;
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;

    QWidget* getWidget(const QString& WID) override;
    QString  getPluginName() override;

private:
    TrayIconRClickWgt* m_RClickWgt;
};
#endif // XPFUIPLUIN_H
