#ifndef XPFDBSERVICEFACRTORYIMPL_H
#define XPFDBSERVICEFACRTORYIMPL_H

#include "IXPFDbServiceFactory.h"
#include <memory>

class XPFDbServiceFacrtoryImpl : public IXPFDbServiceFactory {
public:
    XPFDbServiceFacrtoryImpl();
    ~XPFDbServiceFacrtoryImpl();

private:
    QList<IXPFDbService*> m_DbServices;

    // IXPFDbServiceFactory interface
public:
    std::shared_ptr<IXPFDbService> createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const XPFDbAttribute& attr) override;
};

#endif // XPFDBSERVICEFACRTORY_H
