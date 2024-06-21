#ifndef IXPFPLUGINHELPER_H
#define IXPFPLUGINHELPER_H

#include "IXPFPlugin.h"
#include <QVariant>

class IXPFPluginHelper
{
public:
    IXPFPluginHelper() { }
    virtual ~IXPFPluginHelper() { }

    virtual QString getXPFBinDir() = 0;
    virtual QString getXPFBinConfigDir() = 0;
    virtual void subMessage(IXPFPlugin *plugin, uint32_t msgid) = 0;
    virtual void unsubMessage(IXPFPlugin *plugin, uint32_t msgid) = 0;
    virtual void pubMessage(uint32_t msgid, const QVariant &param) = 0;

};

#endif // IXPFPLUGINHELPER_H
