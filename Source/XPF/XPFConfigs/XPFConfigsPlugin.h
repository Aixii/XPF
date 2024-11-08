#ifndef XPFUIPLUGIN_H
#define XPFUIPLUGIN_H

#include <IXPFPlugin>
#include <QObject>

class XPFConfigsPlugin
    : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFConfigsPlugin();
    ~XPFConfigsPlugin();

    // IXPFPlugin interface
public:
    void initPlugin(IXPFPluginHelper* pluginHelper) override;
    void initAfterPlugin() override;
    void release() override;
    void onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;

    QWidget* getWidget(const QString& WID) override;
    QString  getPluginName() override;
};
#endif // XPFUIPLUGIN_H
