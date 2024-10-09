#ifndef TESTSERIALPORTRECIVER_H
#define TESTSERIALPORTRECIVER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>

class TestSerialPortReciver : public QObject {
    Q_OBJECT
public:
    TestSerialPortReciver(QSerialPort* port, QObject* parent = nullptr);
    ~TestSerialPortReciver();

public slots:
    void slotHandleReadyRead();

signals:
    void sigStartResp(uint8_t irNum, uint8_t respStatus);
    void sigStopResp(uint8_t irNum, uint8_t respStatus);
    void sigInfoResp(uint8_t irNum, uint16_t testPos, uint16_t testV, uint32_t testR, uint16_t testA);
    void sigZeroResp(uint8_t irNUm, uint8_t respStatus);
    void sigLengthResp(uint8_t irNum, uint16_t length);
    void sigVersionResp(QString version);

private:
    QSerialPort* m_port;
    QByteArray   m_bytes;
    uint8_t      m_Current_CMD_Type;
    uint8_t      m_Current_IR_Number;
    uint16_t     m_Current_CMD_Length;
    uint16_t     m_Last_Position;
};

#endif // TESTSERIALPORTRECIVER_H
