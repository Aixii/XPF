#ifndef XPFUIPLUIN_H
#define XPFUIPLUIN_H

#include "IXPFPlugin.h"
#include <QObject>

class XPFUiPluin : public QObject, public IXPFPlugin
{
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFUiPluin();
    ~XPFUiPluin();

    // IXPFPlugin interface
public:
    void initPlugin() override;
    void initBeforePlugin() override;
    QWidget *getWidget(const QString &widget_id) override;
    void release() override;
    void onMessage(uint32_t msgid, const QVariant &param) override;
};

#endif // XPFUIPLUIN_H
