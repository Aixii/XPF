#include "XPFDbServiceWorker.h"
#include "SqlResult.h"
#include <QEventLoop>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>
#include <QVariantMap>

XPFDbServiceWorker::XPFDbServiceWorker(QObject* parent)
    : QObject(parent) {
}

XPFDbServiceWorker::~XPFDbServiceWorker() {
}

bool XPFDbServiceWorker::exec(const QString& sql, ISqlResult** result) {
    SqlResult* ret = new SqlResult;

    QSqlQuery query(m_db);
    query.exec(sql);

    ret->readFromQSqlQuery(query);

    if (result != nullptr) {
        *result = ret;
    }
    else {
        delete ret;
    }

    if (query.lastError().type() != QSqlError::NoError) {
        return false;
    }
    return true;
}

bool XPFDbServiceWorker::insert(const QString& tb_name, const QVariantMap& valueMap, ISqlResult** result) {
    QString sql = QString("INSERT INTO %0 ( %1 ) VALUES ( %2 )").arg(tb_name);

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

    QSqlQuery query(m_db);

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
        SqlResult* rst = new SqlResult;
        rst->readFromQSqlQuery(query);
        *result = rst;
    }

    if (query.lastError().type() != QSqlError::NoError) {
        return false;
    }

    return true;
}

bool XPFDbServiceWorker::update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, ISqlResult** result) {
    QString sql = QString("UPDATE %0 SET %1 WHERE %2").arg(tb_name);

    QString str0;

    QStringList fields = valueMap.keys();

    for (int index = 0; index < fields.size(); index++) {
        const QString& field = fields.at(index);
        str0 += QString("%0=:%1").arg(field).arg(field);
        if (index < fields.size() - 1) {
            str0 += ',';
        }
    }

    sql = sql.arg(str0);

    QString condition;

    if (!condMap.isEmpty()) {
        QMapIterator<QString, QVariant> iter(condMap);
        while (iter.hasNext()) {
            iter.next();
            condition += iter.key();
            condition += "=";
            condition += QString(":_%0").arg(iter.key());

            if (iter.hasNext()) {
                condition += " AND ";
            }
        }

        sql = sql.arg(condition);
    }

    QSqlQuery query(m_db);

    do {
        if (!query.prepare(sql)) {
            break;
        }

        QMapIterator<QString, QVariant> iter(valueMap);

        while (iter.hasNext()) {
            iter.next();
            query.bindValue(":" + iter.key(), iter.value());
        }

        if (!condMap.isEmpty()) {
            QMapIterator<QString, QVariant> iter(condMap);
            while (iter.hasNext()) {
                iter.next();
                query.bindValue(QString(":_%0").arg(iter.key()), iter.value());
            }
        }

        query.exec();
    }
    while (0);

    if (result != nullptr) {
        SqlResult* rst = new SqlResult;
        rst->readFromQSqlQuery(query);
        *result = rst;
    }

    if (query.lastError().type() != QSqlError::NoError) {
        return false;
    }

    return true;
}

bool XPFDbServiceWorker::remove(const QString& tb_name, const QVariantMap& condMap, ISqlResult** result) {
    QString sql = QString("DELETE FROM %0").arg(tb_name);

    QString condition;

    if (!condMap.isEmpty()) {
        QMapIterator<QString, QVariant> iter(condMap);
        while (iter.hasNext()) {
            iter.next();
            condition += iter.key();
            condition += "=";
            condition += QString(":%0").arg(iter.key());

            if (iter.hasNext()) {
                condition += " AND ";
            }
        }

        sql += QString(" WHERE %0").arg(condition);
    }

    QSqlQuery query(m_db);

    do {
        if (!query.prepare(sql)) {
            break;
        }

        if (!condMap.isEmpty()) {
            QMapIterator<QString, QVariant> iter(condMap);
            while (iter.hasNext()) {
                iter.next();
                query.bindValue(QString(":%0").arg(iter.key()), iter.value());
            }
        }

        query.exec();
    }
    while (0);

    if (result != nullptr) {
        SqlResult* rst = new SqlResult;
        rst->readFromQSqlQuery(query);
        *result = rst;
    }

    if (query.lastError().type() != QSqlError::NoError) {
        return false;
    }

    return true;
}

bool XPFDbServiceWorker::select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, ISqlResult** result) {
    QString sql = QString("SELECT %0 FROM %1");

    QString str0 = fields.at(0);
    for (int index = 1; index < fields.size(); index++) {
        str0 += QString(",%0").arg(fields.at(index));
    }

    sql = sql.arg(str0).arg(tb_name);

    QString condition;

    if (!condMap.isEmpty()) {
        QMapIterator<QString, QVariant> iter(condMap);
        while (iter.hasNext()) {
            iter.next();
            condition += iter.key();
            condition += "=";
            condition += QString(":%0").arg(iter.key());

            if (iter.hasNext()) {
                condition += " AND ";
            }
        }

        sql += QString(" WHERE %0").arg(condition);
    }

    QSqlQuery query(m_db);

    do {
        if (!query.prepare(sql)) {
            break;
        }

        if (!condMap.isEmpty()) {
            QMapIterator<QString, QVariant> iter(condMap);
            while (iter.hasNext()) {
                iter.next();
                query.bindValue(QString(":%0").arg(iter.key()), iter.value());
            }
        }

        query.exec();
    }
    while (0);

    if (result != nullptr) {
        SqlResult* rst = new SqlResult;
        rst->readFromQSqlQuery(query);
        *result = rst;
    }

    if (query.lastError().type() != QSqlError::NoError) {
        return false;
    }

    return true;
}

void XPFDbServiceWorker::slotExec(int seq, const QString& sql) {
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "slotExec", Qt::QueuedConnection,
                                  Q_ARG(int, seq),
                                  Q_ARG(const QString&, sql));
        return;
    }

    ISqlResult* ret = nullptr;

    exec(sql, &ret);

    emit sigSqlExecuteResult(seq, ret);
}

void XPFDbServiceWorker::slotInsert(int seq, const QString& tb_name, const QVariantMap& valueMap) {
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "slotInsert", Qt::QueuedConnection,
                                  Q_ARG(int, seq),
                                  Q_ARG(const QString&, tb_name),
                                  Q_ARG(const QVariantMap&, valueMap));
        return;
    }

    ISqlResult* ret = nullptr;

    insert(tb_name, valueMap, &ret);

    emit sigSqlExecuteResult(seq, ret);
}

void XPFDbServiceWorker::slotUpdate(int seq, const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap) {
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "slotUpdate", Qt::QueuedConnection,
                                  Q_ARG(int, seq),
                                  Q_ARG(const QString&, tb_name),
                                  Q_ARG(const QVariantMap&, valueMap),
                                  Q_ARG(const QVariantMap&, condMap));
        return;
    }

    ISqlResult* ret = nullptr;

    update(tb_name, valueMap, condMap, &ret);

    emit sigSqlExecuteResult(seq, ret);
}

void XPFDbServiceWorker::slotRemove(int seq, const QString& tb_name, const QVariantMap& condMap) {
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "slotRemove", Qt::QueuedConnection,
                                  Q_ARG(int, seq),
                                  Q_ARG(const QString&, tb_name),
                                  Q_ARG(const QVariantMap&, condMap));
        return;
    }

    ISqlResult* ret = nullptr;

    remove(tb_name, condMap, &ret);

    emit sigSqlExecuteResult(seq, ret);
}

void XPFDbServiceWorker::slotSelect(int seq, const QString& tb_name, const QStringList& fields, const QVariantMap& condMap) {
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "slotSelect", Qt::QueuedConnection,
                                  Q_ARG(int, seq),
                                  Q_ARG(const QString&, tb_name),
                                  Q_ARG(const QStringList&, fields),
                                  Q_ARG(const QVariantMap&, condMap));
        return;
    }

    ISqlResult* ret = nullptr;

    select(tb_name, fields, condMap, &ret);

    emit sigSqlExecuteResult(seq, ret);
}
