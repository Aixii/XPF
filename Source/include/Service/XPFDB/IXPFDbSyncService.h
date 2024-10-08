#ifndef IXPFDBSYNCSERVICE_H
#define IXPFDBSYNCSERVICE_H

#include "IXPFService.h"
#include "SqlResult.h"
#include <QSqlDriver>
#include <QString>

class IXPFDbSyncService {
public:
    virtual bool exec(const QString& sql, SqlResult** result = nullptr)                                                                = 0;
    virtual bool insert(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result = nullptr)                             = 0;
    virtual bool update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result = nullptr) = 0;
    virtual bool remove(const QString& tb_name, const QString& conditional, SqlResult** result = nullptr)                              = 0;
    virtual bool select(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result = nullptr)   = 0;
};

#endif
