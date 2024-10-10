#include "IRDevicePortDataHandler.h"
#include "IRTestParamDefine.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QDebug>
#include <QSerialPort>
#include <QStackedWidget>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

IRDevicePortDataHandler::IRDevicePortDataHandler() {
    m_port = new QSerialPort();
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setBaudRate(QSerialPort::Baud115200);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    m_reciveThread = new QThread(this);
    m_sendThread   = new QThread(this);

    m_sender  = new TestSerialPortSender(m_port);
    m_reciver = new TestSerialPortReciver(m_port);

    m_reciver->moveToThread(m_reciveThread);
    //    m_sender->moveToThread(m_sendThread);

    QObject::connect(m_port, &QSerialPort::errorOccurred, this, &IRDevicePortDataHandler::slotErrorOccured);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigZeroResp, this, &IRDevicePortDataHandler::slotZeroResp);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigInfoResp, this, &IRDevicePortDataHandler::slotInfoResp);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigLengthResp, this, &IRDevicePortDataHandler::slotLengthResp);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigStartResp, this, &IRDevicePortDataHandler::slotStartResp);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigStopResp, this, &IRDevicePortDataHandler::slotStopResp);
    QObject::connect(m_reciver, &TestSerialPortReciver::sigVersionResp, this, &IRDevicePortDataHandler::slotVersionResp);

    m_reciveThread->start();
    //    m_sendThread->start();
}

IRDevicePortDataHandler::~IRDevicePortDataHandler() {
    m_reciveThread->terminate();
    m_reciveThread->wait();

    m_sendThread->terminate();
    m_sendThread->wait();
}

void IRDevicePortDataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotOnMessage", Qt::QueuedConnection,
                                  Q_ARG(const QString&, topic),
                                  Q_ARG(uint32_t, msgid),
                                  Q_ARG(const QVariant&, param));
        return;
    }

    if (topic == TOPIC_IRTest) {
        switch (msgid) {
        case IR::DEV_SET_PORT_ID: {
            if (m_port->isOpen()) {
                m_port->close();
                g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
            }
            m_port->setPortName(param.toString());
            if (!m_port->open(QSerialPort::ReadWrite)) {
                qDebug() << u8"端口打开失败";
            }
            else {
                g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_CONNECTED_NOTIFY_ID);
            }
        } break;
        case IR::DEV_SET_ZERO_ID: {
            QByteArray bytes = param.toByteArray();

            IR::st_Dev_Cmd* data = reinterpret_cast<IR::st_Dev_Cmd*>(bytes.data());
            if (data->cmd != IR_Test::CMD_ZERO) {
                break;
            }

            m_sender->slotSendSetZero(data->irnum);
        }
        default:
            break;
        }
    }
}

void IRDevicePortDataHandler::slotErrorOccured() {
    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
}

void IRDevicePortDataHandler::slotStartResp(uint8_t irNum, uint8_t respStatus) {
    IR::st_Dev_Cmd_Resp resp;
    resp.cmd   = IR_Test::CMD_STRT;
    resp.irnum = irNum;
    resp.arg0  = respStatus;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd_Resp));

    memcpy(bytes.data(), &resp, sizeof(resp));

    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_START_RESP_ID, bytes);
}

void IRDevicePortDataHandler::slotStopResp(uint8_t irNum, uint8_t respStatus) {
    IR::st_Dev_Cmd_Resp resp;
    resp.cmd   = IR_Test::CMD_STOP;
    resp.irnum = irNum;
    resp.arg0  = respStatus;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd_Resp));

    memcpy(bytes.data(), &resp, sizeof(resp));

    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_START_RESP_ID, bytes);
}

void IRDevicePortDataHandler::slotInfoResp(uint8_t irNum, uint16_t testPos, uint16_t testV, uint32_t testR, uint16_t testA) {
    IR::st_Dev_Cmd_Resp resp;
    resp.cmd   = IR_Test::CMD_INFO;
    resp.irnum = irNum;
    resp.arg0  = testPos;
    resp.arg1  = testV;
    resp.arg2  = testR;
    resp.arg3  = testA;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd_Resp));

    memcpy(bytes.data(), &resp, sizeof(resp));
    qDebug() << bytes;

    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_TEST_DATA_RESP_ID, bytes);
}

void IRDevicePortDataHandler::slotZeroResp(uint8_t irNum, uint8_t respStatus) {
    IR::st_Dev_Cmd_Resp resp;
    resp.cmd   = IR_Test::CMD_ZERO;
    resp.irnum = irNum;
    resp.arg0  = respStatus;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd_Resp));

    memcpy(bytes.data(), &resp, sizeof(resp));
    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_SET_ZERO_RESP_ID, bytes);
}

void IRDevicePortDataHandler::slotLengthResp(uint8_t irNum, uint16_t length) {
    IR::st_Dev_Cmd_Resp resp;
    resp.cmd   = IR_Test::CMD_LENG;
    resp.irnum = irNum;
    resp.arg0  = length;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd_Resp));

    memcpy(bytes.data(), &resp, sizeof(resp));

    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_START_RESP_ID, bytes);
}

void IRDevicePortDataHandler::slotVersionResp(QString version) {
    Q_UNUSED(version)
}
