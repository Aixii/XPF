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

bool XPFDbSyncServiceImpl::update(const QString& tb_name, const QVariantMap& valueMap, const QVariantMap& condMap, SqlResult** result) {
    return m_worker->update(tb_name, valueMap, condMap, result);
}

bool XPFDbSyncServiceImpl::remove(const QString& tb_name, const QVariantMap& condMap, SqlResult** result) {
    return m_worker->remove(tb_name, condMap, result);
}

bool XPFDbSyncServiceImpl::select(const QString& tb_name, const QStringList& fields, const QVariantMap& condMap, SqlResult** result) {
    return m_worker->select(tb_name, fields, condMap, result);
}
