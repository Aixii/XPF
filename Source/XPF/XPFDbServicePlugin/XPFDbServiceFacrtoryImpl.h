#ifndef XPFDBSERVICEFACRTORYIMPL_H
#define XPFDBSERVICEFACRTORYIMPL_H

#include <IXPFDbServiceFactory>
#include <memory>

class XPFDbServiceFacrtoryImpl : public IXPFDbServiceFactory {
public:
    XPFDbServiceFacrtoryImpl();
    ~XPFDbServiceFacrtoryImpl();

private:
    QList<IXPFDbService*> m_DbServices;

    // IXPFDbServiceFactory interface
public:
    std::shared_ptr<IXPFDbService> createXPFDbService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) override;

    std::shared_ptr<IXPFDbSyncService> createXPFDbSyncService(XPFDB::XPFDbDriverType type, const QString& connectName, const QVariantMap& attr) override;

private:
    QString getDriverName(XPFDB::XPFDbDriverType type);
};

#endif // XPFDBSERVICEFACRTORY_H
