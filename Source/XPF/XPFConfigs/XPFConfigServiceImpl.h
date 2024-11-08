#ifndef XPFCONFIGSERVICEIMPL_H
#define XPFCONFIGSERVICEIMPL_H

#include <IXPFConfigService>
#include <QMutex>

class XPFConfigServiceImpl : public IXPFConfigService {
public:
    XPFConfigServiceImpl();
    ~XPFConfigServiceImpl();

    // IXPFConfigService interface
public:
    void registerConfigurator(const QString& name, IXPFConfigurator* configurator) override;

    IXPFConfigurator* getConfigurator(const QString& name) override;

private:
    QMap<QString, IXPFConfigurator*> m_Configuratores;

    QMutex m_Mutex;
};

#endif // XPFCONFIGSERVICEIMPL_H
