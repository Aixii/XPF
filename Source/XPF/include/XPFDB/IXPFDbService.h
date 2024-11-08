#ifndef IXPFDBSERVICE_H
#define IXPFDBSERVICE_H

#include <IXPFService>
#include <QSqlDriver>
#include <QString>
#include <ISqlResult>

typedef void(*XPF_DB_EXE_HANDLER)(int, ISqlResult*);

class IXPFDbService {
public:
    virtual int exec(const QString& sql) = 0;

    virtual int insert(const QString& tb_name, const QVariantMap& valueMap) = 0;

    virtual int update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap) = 0;

    virtual int remove(const QString& tb_name, const QVariantMap& condMap) = 0;

    virtual int select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap) = 0;

    virtual void installSqlExecuteResultHandler(XPF_DB_EXE_HANDLER handler) = 0;
};

#endif // IXPFDBSERVICE_H
