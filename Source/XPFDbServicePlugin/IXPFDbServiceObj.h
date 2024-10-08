#ifndef IXPFDBSERVICEOBJ_H
#define IXPFDBSERVICEOBJ_H

#include <QString>

class IXPFDbServiceObj {
public:
    virtual bool setDataBase(const QString& driverName, const QString& connName) = 0;
    virtual void setDataBaseName(const QString& db_name)                         = 0;
    virtual void setHost(const QString& hostname, uint16_t port)                 = 0;
    virtual bool open()                                                          = 0;
};

#endif // IXPFDBSERVICEOBJ_H
