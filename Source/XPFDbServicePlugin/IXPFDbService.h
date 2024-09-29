#ifndef IXPFDBSERVICE_H
#define IXPFDBSERVICE_H

#include "IXPFService.h"
#include <QSqlDriver>
#include <QString>

class IXPFDbService : public IXPFService {
public:
    IXPFDbService() {
    }
    ~IXPFDbService() {
    }

    void setDBDriver(QSqlDriver* driver)                                                                            = 0;
    bool connect(const QString& connName, const QString& username = QString(), const QString& password = QString()) = 0;

    bool isConnected() = 0;
    bool isOpened()    = 0;
};

#endif // IXPFDBSERVICE_H
