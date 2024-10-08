#ifndef XPFDBSERVICEIMPLPRIVATE_H
#define XPFDBSERVICEIMPLPRIVATE_H

#include "IXPFDbService"
#include "XPFDbServiceObject.h"

class XPFDbServiceImplPrivate : public XPFDbServiceObject {
    Q_OBJECT
public:
    explicit XPFDbServiceImplPrivate(QObject* parent = nullptr);
    ~XPFDbServiceImplPrivate();

    // IXPFDbService interface
public:
    int exec(const QString& sql);
    int insert(const QString& tb_name, const QVariantMap& valueMap);
    int update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional);
    int remove(const QString& tb_name, const QString& conditional);
    int select(const QString& tb_name, const QStringList& fields, const QString& conditional);

private:
    int generateSequenceCode();

signals:
    void sigSqlExecuteResult(int seq, SqlResult* result);
};

#endif // XPFDBSERVICEIMPLPRIVATE_H
