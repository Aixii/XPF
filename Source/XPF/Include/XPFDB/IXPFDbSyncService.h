#ifndef IXPFDBSYNCSERVICE_H
#define IXPFDBSYNCSERVICE_H

#include <IXPFService>
#include <QSqlDriver>
#include <QString>
#include <ISqlResult>

class IXPFDbSyncService {
public:
    virtual bool exec(const QString& sql, ISqlResult** result = nullptr)                                                                = 0;
    virtual bool insert(const QString& tb_name, const QVariantMap& valueMap, ISqlResult** result = nullptr)                             = 0;
    virtual bool update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, ISqlResult** result = nullptr) = 0;
    virtual bool remove(const QString& tb_name, const QVariantMap& condMap, ISqlResult** result = nullptr)                              = 0;
    virtual bool select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, ISqlResult** result = nullptr)   = 0;
};

#endif
