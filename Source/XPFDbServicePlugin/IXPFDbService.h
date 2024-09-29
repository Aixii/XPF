#ifndef IXPFDBSERVICE_H
#define IXPFDBSERVICE_H

#include "IXPFService.h"
#include "SqlResult.h"
#include <QSqlDriver>
#include <QString>

class IXPFDbService : public IXPFService {
public:
    IXPFDbService(const QString& type, const QString& connectName) {
    }
    ~IXPFDbService() {
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
    virtual bool addDataBase(const QString& type, const QString& connectName) = 0;

    virtual bool transaction()                                         = 0;
    virtual bool rollback()                                            = 0;
    virtual void setConnectOptions(const QString& options = QString()) = 0;
    virtual void setDatabaseName(const QString& name)                  = 0;
    virtual void setHostName(const QString& host)                      = 0;
    virtual void setPort(int port)                                     = 0;
    virtual void setUserName(const QString& name)                      = 0;
    virtual void setPassword(const QString& password)                  = 0;

    virtual bool exec(const QString& sql, SqlResult** result = nullptr);
    virtual bool insert(const QString& tb_name, const QString&)
};

#endif // IXPFDBSERVICE_H
