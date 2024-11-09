#pragma once

#include "IXPFConfigurator"
#include "IXPFService"
#include <QString>

static char IID_IXPFConfigService[] = "IID_IXPFConfigService";

class IXPFConfigService : public IXPFService {
public:
    IXPFConfigService() { Q_UNUSED(IID_IXPFConfigService) }
    virtual ~IXPFConfigService() { }

    virtual void registerConfigurator(const QString& name, IXPFConfigurator* configurator) = 0;

    virtual IXPFConfigurator* getConfigurator(const QString& name) = 0;

private:
};
