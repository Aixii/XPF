#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Singleton.h"
#include <QObject>

namespace IRAccountManager {
class DataHandler : public QObject {
    Q_OBJECT
    SINGLETON(DataHandler)
public slots:
    void slotLoginFromWgt(const QString& username, const QString& password);

signals:
    void sigLoginResult(bool ok, const QString& message);
};
}

#endif // DATAHANDLER_H
