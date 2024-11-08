#ifndef XPFDBSERVICEIMPLPRIVATE_H
#define XPFDBSERVICEIMPLPRIVATE_H

#include <IXPFDbService>
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
    int update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap);
    int remove(const QString& tb_name, const QVariantMap& condMap);
    int select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap);
    void installSqlExecuteResultHandler(XPF_DB_EXE_HANDLER handler);

private:
    int generateSequenceCode();

private:
    XPF_DB_EXE_HANDLER m_exe_handler;
};

#endif // XPFDBSERVICEIMPLPRIVATE_H
