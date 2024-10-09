#include "TestSerialPortSender.h"
#include "IRTestParamDefine.h"
#include <QDebug>
#include <QThread>

TestSerialPortSender::TestSerialPortSender(QSerialPort* port, QObject* parent)
    : QObject(parent) {
    qRegisterMetaType<uint8_t>("uint8_t");

    m_port = port;
}

TestSerialPortSender::~TestSerialPortSender() {
}

void TestSerialPortSender::slotSendSetZero(uint8_t irnum) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotSendSetZero", Qt::QueuedConnection, Q_ARG(uint8_t, irnum));
        return;
    }

    if (!m_port->isOpen()) {
        qDebug() << u8"设备未打开";
        return;
    }

    QByteArray bytes;
    bytes.append((uint8_t)IR_Test::CMD_ZERO);
    bytes.append(irnum);
    bytes.append((uint8_t)5);

    uint16_t crc = IR_Test::modbusCRC16((uint8_t*)bytes.data(), bytes.size());
    bytes.append((uint8_t)(crc & 0xFF));
    bytes.append((uint8_t)((crc >> 8) & 0xFF));

    m_port->write(bytes);
}
