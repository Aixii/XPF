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

    bool setDatabase(const QString &driverName, const QString &connName);

private:
    SqlResult *createResultByQuery(QSqlQuery &query);

private:
    XPFDbServiceImplPrivate* d;

    // IXPFDbService interface
public:
    bool transaction() override;
    bool rollback() override;
    bool exec(const QString &sql, SqlResult **result) override;
    bool insert(const QString &tb_name, const QVariantMap &valueMap, SqlResult **result) override;
    bool update(const QString &tb_name, const QVariantMap &valueMap, const QString &conditional, SqlResult **result) override;
    bool remove(const QString &tb_name, const QString &conditional, SqlResult **result) override;
    bool select(const QString &tb_name, const QStringList &fileds, const QString &conditional, SqlResult **result) override;
};

#endif // XPFDB4SQLITESERVICE_H
