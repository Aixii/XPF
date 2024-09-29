#ifndef XPFDBSERVICEFACRTORY_H
#define XPFDBSERVICEFACRTORY_H

#include "IXPFDbService.h"
#include <memory>

class XPFDbServiceFacrtory {
public:
    XPFDbServiceFacrtory();
    ~XPFDbServiceFacrtory();

    std::shared_ptr<XPFDbServiceImpl*> createXPFDbService();

private:
    QList<XPFDbServiceImpl*> m_DbServices;
};

#endif // XPFDBSERVICEFACRTORY_H
