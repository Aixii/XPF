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

    void sigInfoResp(uint8_t irNum, float testPos, uint16_t testV, uint32_t testR, uint16_t testA);

public:
    bool    dev_status;
    uint8_t test_voltage;
    uint8_t test_precision;
    uint8_t test_mode;

    QString work_area;
    QString work_space;
};

#endif // IRTESTMAINDATAHANDLER_H
