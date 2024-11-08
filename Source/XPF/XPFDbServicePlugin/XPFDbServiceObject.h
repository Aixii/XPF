#ifndef XPFDBSERVICEOBJECT_H
#define XPFDBSERVICEOBJECT_H

#include "IXPFDbServiceObj.h"
#include "XPFDbServiceWorker.h"
#include <QObject>

class XPFDbServiceObject : public QObject
    , public IXPFDbServiceObj {
    Q_OBJECT
public:
    explicit XPFDbServiceObject(QObject* parent = nullptr);
    ~XPFDbServiceObject();

    bool setDataBase(const QString& driverName, const QString& connName);
    void setDataBaseName(const QString& db_name);
    void setHost(const QString& hostname, uint16_t port);
    bool open();

protected:
    XPFDbServiceWorker* m_worker;
};

#endif // XPFDBSERVICEPRIVATE_H
