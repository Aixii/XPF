#include "XPFDbServiceObject.h"
#include <QDebug>

XPFDbServiceObject::XPFDbServiceObject(QObject* parent)
    : QObject(parent)
    , m_worker(new XPFDbServiceWorker(this)) {
}

XPFDbServiceObject::~XPFDbServiceObject() {
    m_worker->m_db.close();
}

bool XPFDbServiceObject::setDataBase(const QString& driverName, const QString& connName) {
    if (!QSqlDatabase::contains(connName)) {
        QSqlDatabase::addDatabase(driverName, connName);
    }
    else if (QSqlDatabase::database(connName).driverName() != driverName) {
        qDebug() << QString(u8"已存在非此驱动类型的连接, 驱动类型：%0, 连接名称：%1").arg(driverName).arg(connName);
        return false;
    }
    m_worker->m_db = QSqlDatabase::database(connName);
    return true;
}

void XPFDbServiceObject::setDataBaseName(const QString& db_name) {
    if (!m_worker->m_db.isValid()) {
        qDebug() << u8"未指定数据库类型";
        return;
    }
    m_worker->m_db.setDatabaseName(db_name);
}

void XPFDbServiceObject::setHost(const QString& hostname, uint16_t port) {
    m_worker->m_db.setHostName(hostname);
    m_worker->m_db.setPort(port);
}

bool XPFDbServiceObject::open() {
    bool opened = m_worker->m_db.open();
    if (!opened) {
        qDebug() << QString(u8"打开数据库连接失败: %0").arg(m_worker->m_db.connectionName());
    }
    return opened;
}
