#ifndef IXPFDBSERVICEFACTORY_H
#define IXPFDBSERVICEFACTORY_H

#include "IXPFDbService"
#include <memory>

namespace XPFDB {
enum XPFDbDriverType {
    QDB2,
    QIBASE,
    QMYSQL,
    QOCI,
    QODBC,
    QPSQL,
    QSQLITES,
    QSQLITE2,
    QTDS,
};
}

typedef struct XPFDbAttribute
{
    QString hostname;
    int     port;
    QString username;
    QString password;
    QString connectOption;

    XPFDbAttribute() {
        port = 0;
    }

    bool isValid() {
        if (hostname.isEmpty() || port == 0) {
            return false;
        }
        return true;
    }
} XPFDbAttribute;

class IXPFDbServiceFactory {
public:
    IXPFDbServiceFactory() { }
    ~IXPFDbServiceFactory() { }

    virtual std::shared_ptr<IXPFDbService*> createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const XPFDbAttribute& attr = XPFDbAttribute()) = 0;
};

#endif // IXPFDBSERVICEFACTORY_H
