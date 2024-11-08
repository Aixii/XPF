#include "XPFDbServiceFacrtoryImpl.h"
#include "XPFDbServiceImpl.h"
#include "XPFDbSyncServiceImpl.h"
#include <QVariantMap>
#include <memory>

XPFDbServiceFacrtoryImpl::XPFDbServiceFacrtoryImpl() {
}

XPFDbServiceFacrtoryImpl::~XPFDbServiceFacrtoryImpl() {
}

/***
Driver Type         Description
QDB2                IBM DB2
QIBASE              Borland InterBase Driver
QMYSQL              MySQL Driver
QOCI                Oracle Call Interface Driver
QODBC               ODBC Driver (includes Microsoft SQL Server)
QPSQL               PostgreSQL Driver
QSQLITES            QLite version 3 or above
QSQLITE2            SQLite version 2
QTDS                Sybase Adaptive Server
***/
std::shared_ptr<IXPFDbService> XPFDbServiceFacrtoryImpl::createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) {

    std::shared_ptr<XPFDbServiceImpl> service = std::make_shared<XPFDbServiceImpl>();

    QString driver = getDriverName(type);
    if (driver.isEmpty()) {
        return nullptr;
    }

    if (!service->setDataBase(driver, connectName)) {
        return nullptr;
    }

    service->setDataBaseName(attr.value(XPFDB::ATTR_DBNAME).toString());
    service.get()->open();
    return service;
}

std::shared_ptr<IXPFDbSyncService> XPFDbServiceFacrtoryImpl::createXPFDbSyncService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) {
    std::shared_ptr<XPFDbSyncServiceImpl> service = std::make_shared<XPFDbSyncServiceImpl>();

    QString driver = getDriverName(type);
    if (driver.isEmpty()) {
        return nullptr;
    }

    if (!service->setDataBase(driver, connectName)) {
        return nullptr;
    }

    service->setDataBaseName(attr.value(XPFDB::ATTR_DBNAME).toString());
    service.get()->open();

    return service;
}

QString XPFDbServiceFacrtoryImpl::getDriverName(XPFDB::XPFDbDriverType type) {
    QString driver;
    switch (type) {
    case XPFDB::QSQLITE3:
        driver = "QSQLITE";
        break;
    default:
        break;
    }
    return driver;
}
