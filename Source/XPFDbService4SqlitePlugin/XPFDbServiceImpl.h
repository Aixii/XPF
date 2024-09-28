#ifndef XPFDBSERVICEIMPL_H
#define XPFDBSERVICEIMPL_H

#include "IXPFService.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QString>
#include <QtSql/QSqlRecord>

class XPFDbServiceImplPrivate;

class XPFDbServiceImpl : public IXPFService {

public:
    XPFDbServiceImpl();
    ~XPFDbServiceImpl();

    void setDBDriver(QSqlDriver* driver);
    bool connect(const QString& connName, const QString& username = QString(), const QString& password = QString());

    bool isConnected();
    bool isOpened();

private:
    XPFDbServiceImplPrivate* d;
};

#endif // XPFDB4SQLITESERVICE_H
