#ifndef XPFGLOBAL_H
#define XPFGLOBAL_H

#include <cstdint>
#include <QString>

namespace XPF {

#ifndef XPFGLOBAL_CPP
extern QString xpf_err_msg;
extern int32_t xpf_err_code;
#endif

enum XPF_ERR
{
    XPF_ERR_CONFIG_FILE_NOEXISTS                = 1,
    XPF_ERR_CONFIG_FILE_OPEN_FAILED             = 2,
    XPF_ERR_CONFIG_FILE_PARSE_FAILED            = 3,
    XPF_ERR_CONFIG_NOTAPPNAME                   = 4,
    XPF_ERR_APP_IS_ALREADY_RUNNING              = 5,
    XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT    = 6,
};

QString XPFErrorCode2String(int32_t errcode);

void setXPFErrorCode(int32_t errcode);

}

#endif // XPFGLOBAL_H
