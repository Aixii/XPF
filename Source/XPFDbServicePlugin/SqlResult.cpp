#include "SqlResult.h"
#include "SqlResultPrivate.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

SqlResult::SqlResult(QObject* parent)
    : QObject(parent) {
    d = new SqlResultPrivate(this);
}

SqlResult::~SqlResult() {
}

void SqlResult::readFromQSqlQuery(QSqlQuery query) {
    d->m_datas.clear();
    d->m_fields.clear();

    if (query.isValid()) {
        d->m_valid = false;
        return;
    }
    else {
        d->m_valid = true;
    }

    d->m_error = query.lastError();
    if (d->m_error.type() != QSqlError::NoError) {
        return;
    }

    QSqlRecord record = query.record();

    int fieldcount = record.count();
    for (int index = 0; index < fieldcount; index++) {
        d->m_fields.append(record.field(index).name());
    }

    while (query.next()) {
        QVariantList list;
        for (int index = 0; index < fieldcount; index++) {
            list << query.value(index);
        }

        d->m_datas.append(list);
    }
}

void SqlResult::readFromQSqlDataBase(QSqlDatabase db) {
    if (db.lastError().type() != QSqlError::NoError) {
        d->setError(db.lastError());
    }
}

int SqlResult::fieldsCount() {
    return d->m_fields.size();
}

QStringList SqlResult::fieldes() {
    return d->m_fields;
}

QString SqlResult::fieldName(int index) {
    return d->m_fields.value(index);
}

int SqlResult::fieldIndexOf(const QString& name) {
    return d->m_fields.indexOf(name);
}

int SqlResult::rowCount() {
    return d->m_datas.size();
}

QVariantList SqlResult::row(int rowIndex) {
    return d->m_datas.value(rowIndex);
}

QVariant SqlResult::rowData(int rowIndex, int colunmIndex) {
    if (rowIndex > d->m_datas.size() || colunmIndex > d->m_datas.at(rowIndex).size()) {
        return QVariant();
    }
    return d->m_datas.at(rowIndex).at(colunmIndex);
}

bool SqlResult::isError() {
    if (d->m_error.type() == QSqlError::NoError) {
        return false;
    }
    return true;
}

bool SqlResult::isEmpty() {
    if (d->m_fields.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}

bool SqlResult::isValid() {
    return d->m_valid;
}

QSqlError SqlResult::error() {
    return d->m_error;
}

SqlResult* SqlResult::fromQSqlQuery(QSqlQuery query) {
    SqlResult* result = new SqlResult;
    result->readFromQSqlQuery(query);
    return result;
}
