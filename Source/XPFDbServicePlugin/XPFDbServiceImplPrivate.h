#ifndef XPFDBSERVICEIMPLPRIVATE_H
#define XPFDBSERVICEIMPLPRIVATE_H

#include <QSqlDatabase>
#include <QSqlQuery>

class XPFDbServiceImpl;

class XPFDbServiceImplPrivate {
public:
    XPFDbServiceImplPrivate();
    ~XPFDbServiceImplPrivate();

    friend class XPFDbServiceImpl;

private:
    QSqlDatabase m_db;
    QSqlDriver*  m_driver;
};

#endif // XPFDBSERVICEIMPLPRIVATE_H
