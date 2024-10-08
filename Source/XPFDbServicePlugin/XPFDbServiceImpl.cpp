#include "XPFDbServiceImpl.h"
#include "XPFDbServiceImplPrivate.h"
#include <QSqlQuery>
#include <QVariantMap>
#include <mutex>

XPFDbServiceImpl::XPFDbServiceImpl()
    : IXPFDbService() {
}

XPFDbServiceImpl::~XPFDbServiceImpl() {
}

bool XPFDbServiceImpl::setDatabase(const QString& driverName, const QString& connName) {
    QSqlDatabase::addDatabase(driverName, connName);
}

int XPFDbServiceImpl::exec(const QString& sql) {
    return d->exec(sql);
}

bool XPFDbServiceImpl::execSync(const QString& sql, SqlResult** result) {
    return d->execSync(sql, result);
}

int XPFDbServiceImpl::insert(const QString& tb_name, const QVariantMap& valueMap) {
    return d->insert(tb_name, valueMap);
}

bool XPFDbServiceImpl::insertSync(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) {
    return d->insertSync(tb_name, valueMap, result);
}

int XPFDbServiceImpl::update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional) {
    return d->update(tb_name, valueMap, conditional);
}

bool XPFDbServiceImpl::updateSync(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result) {
    return d->updateSync(tb_name, valueMap, conditional, result);
}

int XPFDbServiceImpl::remove(const QString& tb_name, const QString& conditional) {
    return d->remove(tb_name, conditional);
}

bool XPFDbServiceImpl::removeSync(const QString& tb_name, const QString& conditional, SqlResult** result) {
    return d->removeSync(tb_name, conditional, result);
}

int XPFDbServiceImpl::select(const QString& tb_name, const QStringList& fields, const QString& conditional) {
    return d->select(tb_name, fields, conditional);
}

bool XPFDbServiceImpl::selectSync(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result) {
    return d->selectSync(tb_name, fields, conditional, result);
}
