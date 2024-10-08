#ifndef XPFDBSYNCSERVICEIMPL_H
#define XPFDBSYNCSERVICEIMPL_H

#include "IXPFDbSyncService.h"
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
    bool exec(const QString& sql, SqlResult** result) override;
    bool insert(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) override;
    bool update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, SqlResult** result) override;
    bool remove(const QString& tb_name, const QVariantMap& condMap, SqlResult** result) override;
    bool select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, SqlResult** result) override;
};

#endif // XPFDBSYNCSERVICEIMPL_H
