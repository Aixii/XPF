#include "XPFDbServiceImplPrivate.h"
#include <mutex>

namespace {
int        g_seq = 0;
std::mutex g_seq_mutex;
}

XPFDbServiceImplPrivate::XPFDbServiceImplPrivate(QObject* parent)
    : XPFDbServiceObject(parent) {
}

XPFDbServiceImplPrivate::~XPFDbServiceImplPrivate() {
}

int XPFDbServiceImplPrivate::exec(const QString& sql) {
    int code = generateSequenceCode();
    m_worker->slotExec(code, sql);
    return code;
}

int XPFDbServiceImplPrivate::insert(const QString& tb_name, const QVariantMap& valueMap) {
    int code = generateSequenceCode();
    m_worker->slotInsert(code, tb_name, valueMap);
    return code;
}

int XPFDbServiceImplPrivate::update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotUpdate(code, tb_name, valueMap, conditional);
    return code;
}

int XPFDbServiceImplPrivate::remove(const QString& tb_name, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotRemove(code, tb_name, conditional);
    return code;
}

int XPFDbServiceImplPrivate::select(const QString& tb_name, const QStringList& fields, const QString& conditional) {
    int code = generateSequenceCode();
    m_worker->slotSelect(code, tb_name, fields, conditional);
    return code;
}

int XPFDbServiceImplPrivate::generateSequenceCode() {
    int code = 0;
    g_seq_mutex.lock();
    code = ++g_seq;
    g_seq_mutex.unlock();
    return code;
}
