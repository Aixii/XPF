#ifndef IRMENUHEADERDATAHANDLER_H
#define IRMENUHEADERDATAHANDLER_H

#include "Singleton.h"
#include <QObject>

class IRMenuHeaderDataHandler : public QObject {
    Q_OBJECT
    SINGLETON(IRMenuHeaderDataHandler)
public slots:
    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

    void slotLogoutFromWgt();

signals:
    void sigLoginSucceed();
};

#endif // DATAHANDLER_H
