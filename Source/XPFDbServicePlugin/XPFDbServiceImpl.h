#ifndef XPFDBSERVICEIMPL_H
#define XPFDBSERVICEIMPL_H

#include "IXPFDbService.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QString>
#include <QtSql/QSqlRecord>

class XPFDbServiceImplPrivate;

class XPFDbServiceImpl : public IXPFDbService {

public:
    XPFDbServiceImpl();
    ~XPFDbServiceImpl();

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
    bool addDataBase(const QString& type, const QString& connectName);

    bool isConnected();
    bool isOpened();

private:
    XPFDbServiceImplPrivate* d;
};

#endif // XPFDB4SQLITESERVICE_H
