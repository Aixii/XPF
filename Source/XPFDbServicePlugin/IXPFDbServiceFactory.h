#ifndef IXPFDBSERVICEFACTORY_H
#define IXPFDBSERVICEFACTORY_H

#include "IXPFDbService"
#include <memory>

class IXPFDbServiceFactory {
public:
    IXPFDbServiceFactory() {
    }
    ~IXPFDbServiceFactory() {
    }

    virtual std::shared_ptr<IXPFDbService*> createXPFDbService() = 0;
};

#endif // IXPFDBSERVICEFACTORY_H
