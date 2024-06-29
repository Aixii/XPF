#ifndef XPFPLUGINHELPERIMPL_H
#define XPFPLUGINHELPERIMPL_H

#include "IXPFPluginHelper.h"


class XPFPluginHelperImpl : public IXPFPluginHelper
{


    // IXPFPluginHelper interface
public:
    QString getXPFBinDir() override;

    QString getXPFBinConfigDir() override;

    void subMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void unsubMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void pubMessage(uint32_t msgid, const QVariant &param) override;
};


#endif // XPFPLUGINHELPERIMPL_H
