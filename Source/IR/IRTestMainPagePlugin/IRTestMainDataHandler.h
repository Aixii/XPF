#ifndef IRTESTMAINDATAHANDLER_H
#define IRTESTMAINDATAHANDLER_H

#include "Singleton.h"
#include <QObject>

class IRTestMainDataHandler : public QObject {
    Q_OBJECT
    SINGLETON(IRTestMainDataHandler)
public slots:
    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

signals:
    void sigConnectedNotify();
    void sigDisconnectedNotify();

public:
    bool dev_status;
};

#endif // IRTESTMAINDATAHANDLER_H
