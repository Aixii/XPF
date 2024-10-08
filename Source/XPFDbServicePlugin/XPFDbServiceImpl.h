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
    int update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap) override;
    int remove(const QString& tb_name, const QVariantMap& condMap) override;
    int select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap) override;

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
