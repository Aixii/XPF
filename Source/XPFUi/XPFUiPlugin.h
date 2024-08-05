#ifndef XPFUIPLUGIN_H
#define XPFUIPLUGIN_H

#include "IXPFPlugin.h"
#include <QObject>

class XPFUiPluin
    : public QObject
    , public IXPFPlugin {
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFUiPluin();
    ~XPFUiPluin();

    // IXPFPlugin interface
public:
    void     initPlugin(IXPFPluginHelper* pluginHelper) override;
    void     initAfterPlugin() override;
    void     release() override;
    void     onMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) override;
    QWidget* getWidget(const QString& WID) override;
};
#endif // XPFUIPLUGIN_H
