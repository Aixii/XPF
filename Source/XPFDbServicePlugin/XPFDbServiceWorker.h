#ifndef XPFDBSERVICEWORKER_H
#define XPFDBSERVICEWORKER_H

#include "SqlResult.h"
#include <QObject>
#include <QSqlDatabase>

class XPFDbServiceObject;

class XPFDbServiceWorker : public QObject {
    Q_OBJECT
public:
    explicit XPFDbServiceWorker(QObject* parent = nullptr);
    ~XPFDbServiceWorker();

    friend class XPFDbServiceObject;

    // IXPFDbService interface
public:
    bool exec(const QString& sql, SqlResult** result);
    bool insert(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result);
    bool update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result);
    bool remove(const QString& tb_name, const QString& conditional, SqlResult** result);
    bool select(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result);

public slots:
    void slotExec(int seq, const QString& sql);
    void slotInsert(int seq, const QString& tb_name, const QVariantMap& valueMap);
    void slotUpdate(int seq, const QString& tb_name, const QVariantMap& valueMap, const QString& conditional);
    void slotRemove(int seq, const QString& tb_name, const QString& conditional);
    void slotSelect(int seq, const QString& tb_name, const QStringList& fields, const QString& conditional);

signals:
    void sigSqlExecuteResult(int seq, SqlResult* result);

private:
    QSqlDatabase m_db;
};

#endif // XPFDBSERVICEASYNCWORK_H
