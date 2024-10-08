#include "XPFDbServiceFacrtoryImpl.h"
#include "XPFDbServiceImpl.h"
#include <memory>

XPFDbServiceFacrtoryImpl::XPFDbServiceFacrtoryImpl() {
}

XPFDbServiceFacrtoryImpl::~XPFDbServiceFacrtoryImpl() {
}

std::shared_ptr<IXPFDbService> XPFDbServiceFacrtoryImpl::createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const XPFDbAttribute& attr) {

    XPFDbServiceImpl* service = new XPFDbServiceImpl();

    QString driver;
    switch (type) {
    case XPFDB::QSQLITE3:
        driver = "QSQLITE";
        break;
    default:
        return nullptr;
    }
    if (!service->setDatabase(driver, connectName)) {
        delete service;
        return nullptr;
    }

    return std::make_shared<XPFDbServiceImpl>(service);
}
