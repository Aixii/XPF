#ifndef TESTSERIALPORTSENDER_H
#define TESTSERIALPORTSENDER_H

#include <QObject>
#include <QSerialPort>

class TestSerialPortSender : public QObject {
    Q_OBJECT
public:
    TestSerialPortSender(QSerialPort* port, QObject* parent = nullptr);
    ~TestSerialPortSender();

public slots:
    void slotSendSetZero(uint8_t irnum);

private:
    QSerialPort* m_port;
};

#endif // TESTSERIALPORTSENDER_H
