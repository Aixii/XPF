#ifndef IXPFPLUGIN_H
#define IXPFPLUGIN_H

#include <QObject>
class IXPFPluginHelper;

class IXPFPlugin
{
public:
    IXPFPlugin() { }
    virtual ~IXPFPlugin() { }

    virtual void initPlugin(IXPFPluginHelper *pluginHelper) = 0;

    virtual void initBeforePlugin() = 0;

    virtual QWidget *getWidget(const QString &widget_id) = 0;

    virtual void release() = 0;

    virtual void onMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender) = 0;

};

#define IXPFPlugin_IID "com.xpf.IXPFPlugin"
Q_DECLARE_INTERFACE(IXPFPlugin, IXPFPlugin_IID)

#endif
