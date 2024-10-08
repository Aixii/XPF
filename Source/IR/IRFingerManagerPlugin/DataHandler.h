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

    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

signals:
    void sigLoginResult(bool ok, const QString& message);

private:
    void loginSucceed();
};
}

#endif // DATAHANDLER_H
