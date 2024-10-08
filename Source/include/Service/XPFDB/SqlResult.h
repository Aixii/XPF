#ifndef SQLRESULT_H
#define SQLRESULT_H

#include <QObject>

class QSqlError;
class QSqlQuery;
class QSqlDatabase;
class SqlResultPrivate;

class Q_DECL_EXPORT SqlResult : public QObject {
    Q_OBJECT
public:
    explicit SqlResult(QObject* parent = nullptr);
    ~SqlResult();

    void readFromQSqlQuery(QSqlQuery query);
    void readFromQSqlDataBase(QSqlDatabase db);

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
