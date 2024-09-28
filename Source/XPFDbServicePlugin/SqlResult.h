#ifndef SQLRESULT_H
#define SQLRESULT_H

#include <QObject>
#include <QSqlError>
#include <QSqlQuery>

class SqlResultPrivate;

class SqlResult : public QObject {
    Q_OBJECT
public:
    explicit SqlResult(QObject* parent = nullptr);
    ~SqlResult();

    void readFromQSqlQuery(QSqlQuery query);

    int fieldsCount();

    QStringList fieldes();
    QString     fieldName(int index);
    int         fieldIndexOf(const QString& name);

    int rowCount();

    QVariantList row(int rowIndex);
    QVariant     rowData(int rowIndex, int colunmIndex);

    bool isError();
    bool isEmpty();
    bool isValid();

    QSqlError error();

    static SqlResult* fromQSqlQuery(QSqlQuery query);

private:
    SqlResultPrivate* d;
};

#endif // SQLRESULT_H
