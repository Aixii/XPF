#ifndef XPFDBSYNCSERVICEIMPL_H
#define XPFDBSYNCSERVICEIMPL_H

#include <IXPFDbSyncService>
#include "XPFDbServiceObject.h"
#include "XPFDbServiceWorker.h"

class XPFDbSyncServiceImpl : public XPFDbServiceObject
    , public IXPFDbSyncService {
    Q_OBJECT
public:
    XPFDbSyncServiceImpl();
    ~XPFDbSyncServiceImpl();

    // IXPFDbSyncService interface
public:
    bool exec(const QString& sql, ISqlResult** result) override;
    bool insert(const QString& tb_name, const QVariantMap& valueMap, ISqlResult** result) override;
    bool update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, ISqlResult** result) override;
    bool remove(const QString& tb_name, const QVariantMap& condMap, ISqlResult** result) override;
    bool select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, ISqlResult** result) override;
};

#endif // XPFDBSYNCSERVICEIMPL_H
