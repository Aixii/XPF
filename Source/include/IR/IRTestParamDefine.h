#ifndef IRTESTPARAMDEFINE_H
#define IRTESTPARAMDEFINE_H

#include <QByteArray>
#include <QMetaType>
#include <stdint.h>

namespace IR_Test {
enum IR_VG : uint8_t {
    VG_500V  = 0,
    VG_1500V = 1,
    VG_2000V = 2,
    VG_2500V = 3,
};

enum IR_Precision {
    PREC_0_1000M = 0,
    PREC_1G_10G  = 1,
};

enum IR_TestMode {
    MODE_FULL    = 0x1,
    MODE_SECTION = 0x2,
};

enum CMD_Type : uint8_t {
    CMD_NONE = 0,
    CMD_STRT = 0xA1,
    CMD_STOP = 0xA2,
    CMD_INFO = 0xA3,
    CMD_ZERO = 0xA4,
    CMD_LENG = 0xA5,
    CMD_VERS = 'L',
};

enum IR_Number : uint8_t {
    IR_NONE = 0,
    IR_1    = 0x1,
    IR_2    = 0x2,
    IR_3    = 0x4,
    IR_ALL  = 0xFF,
};

enum RESP_Status : uint8_t {
    RESP_SUCCESS   = 0x1,
    RESP_FAILED    = 0x2,
    RESP_CMD_ERROR = 0x3,
};

uint16_t toUint16FromBigEndian(const char* pStart);
uint32_t toUint32FromBigEndian(const char* pStart);
uint16_t modbusCRC16(QByteArray data);
uint16_t modbusCRC16(unsigned char* data, unsigned int len);

void appendUint16ToByteArray(QByteArray& byteArray, uint16_t value);
void appendUint32ToByteArray(QByteArray& byteArray, uint32_t value);

}

Q_DECLARE_METATYPE(IR_Test::IR_VG)
Q_DECLARE_METATYPE(IR_Test::IR_Precision)
Q_DECLARE_METATYPE(IR_Test::IR_TestMode)
Q_DECLARE_METATYPE(IR_Test::CMD_Type)
Q_DECLARE_METATYPE(IR_Test::IR_Number)

#endif // IRTESTPARAMDEFINE_H
