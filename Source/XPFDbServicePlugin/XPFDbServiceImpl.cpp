#include "XPFDbServiceImpl.h"
#include "XPFDbServiceImplPrivate.h"
#include <QSqlQuery>
#include <QVariantMap>

XPFDbServiceImpl::XPFDbServiceImpl() {
}

XPFDbServiceImpl::~XPFDbServiceImpl() {
}

bool XPFDbServiceImpl::transaction() {
    return d->m_db.transaction();
}

bool XPFDbServiceImpl::rollback() {
    return d->m_db.rollback();
}

bool XPFDbServiceImpl::exec(const QString& sql, SqlResult** result) {
    SqlResult* ret = new SqlResult;

    QSqlQuery query;
    query.exec(sql);

    ret->readFromQSqlQuery(query);

    if (result != nullptr) {
        *result = ret;
    }
    else {
        delete ret;
    }

    if (query.lastError() != QSqlError::NoError) {
        return false;
    }
    return true;
}

bool XPFDbServiceImpl::insert(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) {
    QString     sql    = QString("INSERT INTO %0 ( %1 ) VALUES ( %2 )").arg(tb_name);
    QStringList fields = valueMap.keys();

    QString str0;
    QString str1;

    for (int index = 0; index < fields.size(); index++) {
        QString field = fields.at(index);
        str0 += field;
        str1 += QString(":%0").arg(field);

        if (index == fields.size() - 1) {
            break;
        }

        str0 += ", ";
        str1 += ", ";
    }

    sql = sql.arg(str0).arg(str1);

    QSqlQuery query(d->m_db);

    do {
        if (!query.prepare(sql)) {
            break;
        }

        QMapIterator<QString, QVariant> iter(valueMap);
        while (iter.hasNext()) {
            iter.next();
            query.bindValue(QString(":%0").arg(iter.key()), iter.value());
        }

        query.exec();
    }
    while (0);

    if (result != nullptr) {
        *result = new SqlResult;
        (*result)->readFromQSqlQuery(query);
    }

    if (query.lastError() != QSqlError::NoError) {
        return false;
    }

    return true;
}

bool XPFDbServiceImpl::update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result) {
    QString sql = QString("UPDATE %0 SET %1 WHERE %2").arg(tb_name);

    QString str0;

    QStringList fields;

    for (int index = 0; index < fields.size(); index++) {
        const QString& field = fields.at(index);
        str0 += QString("%0=:%1").arg(field).arg(field);
        if (index < fields.size() - 1) {
            str0 += ',';
        }
    }

    sql = sql.arg(str0).arg(conditional);

    QSqlQuery query;

    do {
        if (!query.prepare(sql)) {
            break;
        }

        QMapIterator<QString, QVariant> iter(valueMap);

        while (iter.hasNext()) {
            iter.next();
            query.bindValue(":" + iter.key(), iter.value());
        }

        query.exec();
    }
    while (0);

    if (result != nullptr) {
        *result = new SqlResult;
        (*result)->readFromQSqlQuery(query);
    }

    if (query.lastError() != QSqlError::NoError) {
        return false;
    }

    return true;
}

bool XPFDbServiceImpl::remove(const QString& tb_name, const QString& conditional, SqlResult** result) {
}

bool XPFDbServiceImpl::setDatabase(const QString& connName) {
    d->m_db = QSqlDatabase::database(connName);
    if (d->m_db.isValid()) {
        return true;
    }
    return false;
}
