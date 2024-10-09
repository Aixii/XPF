#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Singleton.h"
#include "TestSerialPortReciver.h"
#include "TestSerialPortSender.h"
#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>

class IRDevicePortDataHandler : public QObject {
    Q_OBJECT
    SINGLETON(IRDevicePortDataHandler)
public slots:
    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

private:
    void slotErrorOccured();

private slots:
    void slotStartResp(uint8_t irNum, uint8_t respStatus);
    void slotStopResp(uint8_t irNum, uint8_t respStatus);
    void slotInfoResp(uint8_t irNum, uint16_t testPos, uint16_t testV, uint32_t testR, uint16_t testA);
    void slotZeroResp(uint8_t irNUm, uint8_t respStatus);
    void slotLengthResp(uint8_t irNum, uint16_t length);
    void slotVersionResp(QString version);

private:
    TestSerialPortReciver* m_reciver;
    TestSerialPortSender*  m_sender;
    QSerialPort*           m_port;
    QThread*               m_reciveThread;
    QThread*               m_sendThread;
};

#endif // DATAHANDLER_H
