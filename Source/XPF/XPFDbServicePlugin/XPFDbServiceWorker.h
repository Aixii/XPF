#ifndef XPFDBSERVICEWORKER_H
#define XPFDBSERVICEWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <ISqlResult>

class XPFDbServiceObject;

class XPFDbServiceWorker : public QObject {
    Q_OBJECT
public:
    explicit XPFDbServiceWorker(QObject* parent = nullptr);
    ~XPFDbServiceWorker();

    friend class XPFDbServiceObject;

    // IXPFDbService interface
public:
    bool exec(const QString& sql, ISqlResult** result);
    bool insert(const QString& tb_name, const QVariantMap& valueMap, ISqlResult** result);
    bool update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, ISqlResult** result);
    bool remove(const QString& tb_name, const QVariantMap& condMap, ISqlResult** result);
    bool select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, ISqlResult** result);

public slots:
    void slotExec(int seq, const QString& sql);
    void slotInsert(int seq, const QString& tb_name, const QVariantMap& valueMap);
    void slotUpdate(int seq, const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap);
    void slotRemove(int seq, const QString& tb_name, const QVariantMap& condMap);
    void slotSelect(int seq, const QString& tb_name, const QStringList& fields, const QVariantMap& condMap);

signals:
    void sigSqlExecuteResult(int seq, ISqlResult* result);

private:
    QSqlDatabase m_db;
};

#endif // XPFDBSERVICEASYNCWORK_H
