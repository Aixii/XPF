#include "TestSerialPortReciver.h"
#include "IRTestParamDefine.h"

using namespace IR_Test;

uint16_t IR_Test::toUint16FromBigEndian(const char* pStart) {
    return (static_cast<uint16_t>(pStart[0]) << 8) | static_cast<uint16_t>(pStart[1]);
}

uint32_t IR_Test::toUint32FromBigEndian(const char* pStart) {
    return (static_cast<uint32_t>(pStart[0]) << 24) | (static_cast<uint32_t>(pStart[1]) << 16) | (static_cast<uint32_t>(pStart[2]) << 8) | (static_cast<uint32_t>(pStart[3]));
}

const uint16_t auch_crc[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0, 0x0780, 0xC741, 0x0500,
    0xC5C1, 0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1,
    0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81,
    0x1A40, 0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1, 0xD581, 0x1540,
    0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001,
    0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0,
    0x3480, 0xF441, 0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0, 0x3B80,
    0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40, 0xE401, 0x24C0, 0x2580, 0xE541, 0x2700,
    0xE7C1, 0xE681, 0x2640, 0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041, 0xA001, 0x60C0,
    0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480,
    0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41,
    0x6900, 0xA9C1, 0xA881, 0x6840, 0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01,
    0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1,
    0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041, 0x5000, 0x90C1, 0x9181,
    0x5140, 0x9301, 0x53C0, 0x5280, 0x9241, 0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901,
    0x59C0, 0x5880, 0x9841, 0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40, 0x4E00, 0x8EC1,
    0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41, 0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680,
    0x8641, 0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

// CRC16计算函数
uint16_t IR_Test::modbusCRC16(QByteArray senddata) {
    unsigned int  crc_data = 0xffff; //0xff与数据异或就相当于取反，故只需要一开始把CRC初始值设置为0xffff即可
    unsigned char index;

    for (int i = 0; i < senddata.size() - 2; i++) {
        index = (crc_data & 0xFF) ^ senddata.at(i); //取上一字节的CRC低八位，与本字节异或
        crc_data >>= 8; //取上一字节的高八位
        crc_data ^= auch_crc[index]; //与查表后的结果异或
    }

    return crc_data;
}

uint16_t IR_Test::modbusCRC16(unsigned char* data, unsigned int len) {
    uint16_t i, j, tmp, CRC16;

    CRC16 = 0xFFFF; //CRC寄存器初始值
    for (i = 0; i < len; i++) {
        CRC16 ^= data[i];
        for (j = 0; j < 8; j++) {
            tmp = (uint16_t)(CRC16 & 0x0001);
            CRC16 >>= 1;
            if (tmp == 1) {
                CRC16 ^= 0xA001; //异或多项式
            }
        }
    }
    return CRC16;
}

void IR_Test::appendUint16ToByteArray(QByteArray& byteArray, uint16_t value) {
    byteArray.append(static_cast<char>((value >> 8) & 0xFF)); // 高字节
    byteArray.append(static_cast<char>(value & 0xFF)); // 低字节
}

void IR_Test::appendUint32ToByteArray(QByteArray& byteArray, uint32_t value) {
    byteArray.append(static_cast<char>((value >> 24) & 0xFF));
    byteArray.append(static_cast<char>((value >> 16) & 0xFF));
    byteArray.append(static_cast<char>((value >> 8) & 0xFF));
    byteArray.append(static_cast<char>(value & 0xFF));
}

TestSerialPortReciver::TestSerialPortReciver(QSerialPort* port, QObject* parent)
    : QObject(parent)
    , m_port(port) {

    qRegisterMetaType<uint16_t>("uint16_t");

    m_Last_Position      = -1;
    m_Current_CMD_Length = -1;
    m_Current_CMD_Type   = CMD_NONE;
    m_Current_IR_Number  = 0;

    QObject::connect(port, &QSerialPort::readyRead, this, &TestSerialPortReciver::slotHandleReadyRead);
}

TestSerialPortReciver::~TestSerialPortReciver() {
}

void TestSerialPortReciver::slotHandleReadyRead() {
    QByteArray bytes = m_port->readAll();
    for (int index = 0; index < bytes.size(); index++) {
        unsigned char byte = (unsigned char)bytes.at(index);
        if (m_bytes.size() == 0) {
            switch (byte) {
            case CMD_STRT:
            case CMD_STOP:
            case CMD_INFO:
            case CMD_ZERO:
            case CMD_LENG:
#if 0
            case VERS_CMD:
#endif
                m_Current_CMD_Type = (CMD_Type)byte;
                break;
            default:
                m_Current_CMD_Type = CMD_NONE;
                break;
            }
            if (m_Current_CMD_Type == CMD_NONE) {
                continue;
            }
            m_bytes.append(byte);
        }
        else if (m_bytes.size() == 1) {
            m_Current_IR_Number = (IR_Number)byte;
            m_bytes.append(byte);
        }
        else if (m_bytes.size() == 2) {
            m_Current_CMD_Length = byte;
            m_bytes.append(byte);
        }
        else if (m_bytes.size() < m_Current_CMD_Length) {
            m_bytes.append(byte);
        }
        if (m_bytes.size() == m_Current_CMD_Length) {
            bool check = true;
            // CRC 校验
            QByteArray bytes = m_bytes.left(m_bytes.size() - 2);

            uint16_t crc  = modbusCRC16((uint8_t*)bytes.data(), bytes.size());
            uint8_t  crcL = (uint8_t)(crc >> 8);
            uint8_t  crcH = (uint8_t)(crc & 0xFF);

            uint8_t bcH = (uint8_t)m_bytes.at(m_bytes.size() - 2);
            uint8_t bcL = (uint8_t)m_bytes.at(m_bytes.size() - 1);

            if (crcH != bcH || crcL != bcL) {
                check = false;
            }

            if (check) {
                switch (m_Current_CMD_Type) {
                case CMD_STRT:
                    emit sigStartResp(m_Current_IR_Number, m_bytes.at(3));
                    break;
                case CMD_STOP:
                    emit sigStopResp(m_Current_IR_Number, m_bytes.at(3));
                    break;
                case CMD_ZERO:
                    emit sigZeroResp(m_Current_IR_Number, m_bytes.at(3));
                    break;
                case CMD_INFO: {
#if 0
                    uint16_t pos = toUint16FromBigEndian(m_bytes.data() + 3);
                    if (m_Last_Position == pos) {
                        break;
                    }
#endif
                    emit sigInfoResp(m_Current_IR_Number,
                                     toUint16FromBigEndian(m_bytes.data() + 3),
                                     toUint16FromBigEndian(m_bytes.data() + 5),
                                     toUint32FromBigEndian(m_bytes.data() + 7),
                                     toUint32FromBigEndian(m_bytes.data() + 11));
#if 0
                    m_Last_Position = pos;
#endif
                    break;
                }
                case CMD_LENG: {
                    uint16_t length = toUint16FromBigEndian(m_bytes.data() + 3);

                    emit sigLengthResp(m_Current_IR_Number, length);
                    break;
                }
                default:
                    break;
                }
            }
            m_bytes.resize(0);
            m_Current_IR_Number  = IR_NONE;
            m_Current_CMD_Length = -1;
        }
    }
}
