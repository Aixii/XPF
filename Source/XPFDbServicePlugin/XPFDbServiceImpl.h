#ifndef XPFDBSERVICEIMPL_H
#define XPFDBSERVICEIMPL_H

#include "IXPFDbService.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QString>
#include <QtSql/QSqlRecord>

class XPFDbServiceImplPrivate;

class XPFDbServiceImpl : public IXPFDbService {
    Q_OBJECT
public:
    XPFDbServiceImpl();
    ~XPFDbServiceImpl();

    bool setDatabase(const QString& driverName, const QString& connName);

private:
    SqlResult* createResultByQuery(QSqlQuery& query);

private:
    XPFDbServiceImplPrivate* d;

    // IXPFDbService interface
public:
    int  exec(const QString& sql) override;
    bool execSync(const QString& sql, SqlResult** result) override;

    int  insert(const QString& tb_name, const QVariantMap& valueMap) override;
    bool insertSync(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) override;

    int  update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional) override;
    bool updateSync(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result) override;

    int  remove(const QString& tb_name, const QString& conditional) override;
    bool removeSync(const QString& tb_name, const QString& conditional, SqlResult** result) override;

    int  select(const QString& tb_name, const QStringList& fields, const QString& conditional) override;
    bool selectSync(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result) override;
};

#endif // XPFDB4SQLITESERVICE_H
