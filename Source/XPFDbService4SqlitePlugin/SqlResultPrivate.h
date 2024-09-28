#ifndef SQLRESULTPRIVATE_H
#define SQLRESULTPRIVATE_H

#include <QObject>
#include <QSqlError>

class SqlResult;

class SqlResultPrivate : public QObject {
    Q_OBJECT
public:
    explicit SqlResultPrivate(QObject* parent = nullptr);
    ~SqlResultPrivate();

    void setError(const QSqlError& error);

    friend class SqlResult;

private:
    QStringList         m_fields;
    QList<QVariantList> m_datas;
    QSqlError           m_error;
    bool                m_valid;
};

#endif // SQLRESULTPRIVATE_H
