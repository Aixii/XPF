#ifndef XPFDBSERVICEIMPLPRIVATE_H
#define XPFDBSERVICEIMPLPRIVATE_H

#include "IXPFDbService"
#include <QSqlDatabase>
#include <QSqlQuery>

class XPFDbServiceImpl;

class XPFDbServiceWorker;

class XPFDbServiceImplPrivate : public IXPFDbService {
    Q_OBJECT
public:
    XPFDbServiceImplPrivate();
    ~XPFDbServiceImplPrivate();

    bool addDataBase(const QString& driverName, const QString& connName);

    friend class XPFDbServiceImpl;

private:
    QSqlDatabase        m_db;
    XPFDbServiceWorker* m_worker;

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

private:
    int generateSequenceCode();
};

#endif // XPFDBSERVICEIMPLPRIVATE_H
