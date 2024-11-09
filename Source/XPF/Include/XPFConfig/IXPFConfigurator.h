#pragma once

#include <QString>
#include <QVariant>

class IXPFConfigurator {
public:
    IXPFConfigurator() { }
    virtual ~IXPFConfigurator() { }

    virtual QVariant getConfigItem(const QString& config_key) = 0;

    virtual void setConfigItem(const QString& config_key, const QVariant& var) = 0;
};
