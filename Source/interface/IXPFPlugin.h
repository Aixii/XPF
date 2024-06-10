#ifndef IXPFPLUGIN_H
#define IXPFPLUGIN_H

#include <QObject>

class IXPFPlugin
{
    IXPFPlugin() { }
    virtual ~IXPFPlugin() { }


};

#define IXPFPlugin_IID "com.xpf.IXPFPlugin"
Q_DECLARE_INTERFACE(IXPFPlugin, IXPFPlugin_IID)

#endif
