#include "XPFDbSyncServiceImpl.h"
#include <QDebug>

XPFDbSyncServiceImpl::XPFDbSyncServiceImpl()
    : IXPFDbSyncService() {
}

XPFDbSyncServiceImpl::~XPFDbSyncServiceImpl() {
}

bool XPFDbSyncServiceImpl::exec(const QString& sql, SqlResult** result) {
    return m_worker->exec(sql, result);
}

bool XPFDbSyncServiceImpl::insert(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) {
    return m_worker->insert(tb_name, valueMap, result);
}

bool XPFDbSyncServiceImpl::update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result) {
    return m_worker->update(tb_name, valueMap, conditional, result);
}

bool XPFDbSyncServiceImpl::remove(const QString& tb_name, const QString& conditional, SqlResult** result) {
    return m_worker->remove(tb_name, conditional, result);
}

bool XPFDbSyncServiceImpl::select(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result) {
    return m_worker->select(tb_name, fields, conditional, result);
}
