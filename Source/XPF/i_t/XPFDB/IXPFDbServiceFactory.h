#ifndef IXPFDBSERVICEFACTORY_H
#define IXPFDBSERVICEFACTORY_H

#include <IXPFDbService>
#include <IXPFDbSyncService>
#include <memory>

static char IXPFDbServiceFactoryIID[] = "IXPFDbServiceFactoryIID";

namespace XPFDB {
enum XPFDbDriverType {
    QDB2,
    QIBASE,
    QMYSQL,
    QOCI,
    QODBC,
    QPSQL,
    QSQLITE3,
    QSQLITE2,
    QTDS,
};

static char ATTR_DBNAME[]     = "db_name";
static char ATTR_HOSTNAME[]   = "hostname";
static char ATTR_PORT[]       = "port";
static char ATTR_PASSWORD[]   = "password";
static char ATTR_CONNECTOPT[] = "connect_option";
}

class IXPFDbServiceFactory : public IXPFService {
public:
    IXPFDbServiceFactory() {
        (void)IXPFDbServiceFactoryIID;
        (void)XPFDB::ATTR_DBNAME;
        (void)XPFDB::ATTR_HOSTNAME;
        (void)XPFDB::ATTR_PORT;
        (void)XPFDB::ATTR_PASSWORD;
        (void)XPFDB::ATTR_CONNECTOPT;
    }
    ~IXPFDbServiceFactory() {
    }

    virtual std::shared_ptr<IXPFDbService> createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) = 0;

    virtual std::shared_ptr<IXPFDbSyncService> createXPFDbSyncService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) = 0;
};

#endif // IXPFDBSERVICEFACTORY_H
