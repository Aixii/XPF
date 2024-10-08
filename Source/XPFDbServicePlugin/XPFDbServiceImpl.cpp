#include "XPFDbServiceImpl.h"
#include "SqlResult.h"
#include "XPFDbServiceWorker.h"
#include <QDebug>
#include <QThread>
#include <mutex>

XPFDbServiceImpl::XPFDbServiceImpl() {
    m_thread = new QThread(this);

    d = new XPFDbServiceImplPrivate();
    d->moveToThread(m_thread);

    QObject::connect(d, &XPFDbServiceImplPrivate::sigSqlExecuteResult, this, &XPFDbServiceImpl::sigSqlExecuteResult);

    m_thread->start();
}

XPFDbServiceImpl::~XPFDbServiceImpl() {
    m_thread->terminate();
    m_thread->wait();

    delete d;
}

int XPFDbServiceImpl::exec(const QString& sql) {
    return d->exec(sql);
}

int XPFDbServiceImpl::insert(const QString& tb_name, const QVariantMap& valueMap) {
    return d->insert(tb_name, valueMap);
}

int XPFDbServiceImpl::update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap) {
    return d->update(tb_name, valueMap, condMap);
}

int XPFDbServiceImpl::remove(const QString& tb_name, const QVariantMap& condMap) {
    return d->remove(tb_name, condMap);
}

int XPFDbServiceImpl::select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap) {
    return d->select(tb_name, fields, condMap);
}

bool XPFDbServiceImpl::setDataBase(const QString& driverName, const QString& connName) {
    return d->setDataBase(driverName, connName);
}

void XPFDbServiceImpl::setDataBaseName(const QString& db_name) {
    d->setDataBaseName(db_name);
}

void XPFDbServiceImpl::setHost(const QString& hostname, uint16_t port) {
    d->setHost(hostname, port);
}

bool XPFDbServiceImpl::open() {
    return d->open();
}
