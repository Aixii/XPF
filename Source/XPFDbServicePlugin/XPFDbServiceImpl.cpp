#include "XPFDbServiceImpl.h"
#include "XPFDbServiceImplPrivate.h"

XPFDbServiceImpl::XPFDbServiceImpl() {
}

XPFDbServiceImpl::~XPFDbServiceImpl() {
}

bool XPFDbServiceImpl::addDataBase(const QString& type, const QString& connectName) {
    if (!d->m_db.isDriverAvailable(type)) {
        return false;
    }
    d->m_db = QSqlDatabase::addDatabase(type, connectName);
    if (d->m_db.isValid()) {
        return true;
    }
    return false;
}
