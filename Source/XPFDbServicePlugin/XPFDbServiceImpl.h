#ifndef XPFDBSERVICEIMPL_H
#define XPFDBSERVICEIMPL_H

#include "IXPFDbService"
#include "XPFDbServiceImplPrivate.h"
#include "XPFDbServiceObject.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class XPFDbServiceWorker;

class XPFDbServiceImpl : public IXPFDbService
    , public IXPFDbServiceObj {
    Q_OBJECT
public:
    XPFDbServiceImpl();
    ~XPFDbServiceImpl();

    // IXPFDbService interface
public:
    int exec(const QString& sql) override;
    int insert(const QString& tb_name, const QVariantMap& valueMap) override;
    int update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional) override;
    int remove(const QString& tb_name, const QString& conditional) override;
    int select(const QString& tb_name, const QStringList& fields, const QString& conditional) override;

    // IXPFDbServiceObj interface
public:
    bool setDataBase(const QString& driverName, const QString& connName) override;
    void setDataBaseName(const QString& db_name) override;
    void setHost(const QString& hostname, uint16_t port) override;
    bool open();

private:
    XPFDbServiceImplPrivate* d;
    QThread*                 m_thread;
};

#endif // XPFDbServiceImpl_H
