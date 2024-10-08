#ifndef IXPFDBSERVICE_H
#define IXPFDBSERVICE_H

#include "IXPFService.h"
#include "SqlResult.h"
#include <QSqlDriver>
#include <QString>

class IXPFDbService : public QObject {
    Q_OBJECT
public:
    virtual int exec(const QString& sql) = 0;

    virtual int insert(const QString& tb_name, const QVariantMap& valueMap) = 0;

    virtual int update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap) = 0;

    virtual int remove(const QString& tb_name, const QVariantMap& condMap) = 0;

    virtual int select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap) = 0;

signals:
    void sigSqlExecuteResult(int seq, SqlResult* result);
};

#endif // IXPFDBSERVICE_H
