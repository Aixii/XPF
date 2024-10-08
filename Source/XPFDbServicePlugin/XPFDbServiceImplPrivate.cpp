#include "XPFDbServiceImplPrivate.h"
#include "XPFDbServiceWorker.h"
#include <mutex>

namespace {
int        g_seq = 0;
std::mutex g_seq_mutex;
}

XPFDbServiceImplPrivate::XPFDbServiceImplPrivate() {
}

bool XPFDbServiceImplPrivate::addDataBase(const QString& driverName, const QString& connName) {
    m_worker->
}

int XPFDbServiceImplPrivate::exec(const QString& sql) {
    int code = generateSequenceCode();
    m_worker->slotExec(code, sql);
    return code;
}

bool XPFDbServiceImplPrivate::execSync(const QString& sql, SqlResult** result) {
    return m_worker->exec(sql, result);
}

int XPFDbServiceImplPrivate::insert(const QString& tb_name, const QVariantMap& valueMap) {
    int code = generateSequenceCode();
    m_worker->slotInsert(code, tb_name, valueMap);
    return code;
}

bool XPFDbServiceImplPrivate::insertSync(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result) {
    return m_worker->insert(tb_name, valueMap, result);
}

int XPFDbServiceImplPrivate::update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotUpdate(code, tb_name, valueMap, conditional);
    return code;
}

bool XPFDbServiceImplPrivate::updateSync(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result) {
    return m_worker->update(tb_name, valueMap, conditional, result);
}

int XPFDbServiceImplPrivate::remove(const QString& tb_name, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotRemove(code, tb_name, conditional);
    return code;
}

bool XPFDbServiceImplPrivate::removeSync(const QString& tb_name, const QString& conditional, SqlResult** result) {
    return m_worker->remove(tb_name, conditional, result);
}

int XPFDbServiceImplPrivate::select(const QString& tb_name, const QStringList& fields, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotSelect(code, tb_name, fields, conditional);
    return code;
}

bool XPFDbServiceImplPrivate::selectSync(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result) {
    return m_worker->select(tb_name, fields, conditional, result);
}

int XPFDbServiceImplPrivate::generateSequenceCode() {
    int code = 0;
    g_seq_mutex.lock();
    code = ++g_seq;
    g_seq_mutex.unlock();
    return code;
}
