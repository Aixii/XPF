#ifndef IXPFPLUGINHELPER_H
#define IXPFPLUGINHELPER_H

#include "IXPFPlugin.h"

class IXPFPluginHelper
{
public:
    IXPFPluginHelper() { }
    virtual ~IXPFPluginHelper() { }

    virtual QString getXPFBinDir() = 0;
    virtual QString getXPFBinConfigDir() = 0;
    virtual QWidget* getXPFScreenWidget(int screenID) = 0;
    virtual void subMessage(IXPFPlugin *plugin, uint32_t msgid) = 0;
    virtual void unsubMessage(IXPFPlugin *plugin, uint32_t msgid) = 0;
    virtual void sendMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender) = 0;
    virtual void sendSyncMessage(uint32_t msgid, const QVariant &param, IXPFPlugin *sender) = 0;

};

#endif // IXPFPLUGINHELPER_H
