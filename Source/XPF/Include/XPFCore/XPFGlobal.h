#ifndef XPFGLOBAL_H
#define XPFGLOBAL_H

#include <QString>
#include <cstdint>

namespace XPF {

#ifndef XPFGLOBAL_CPP
extern QString xpf_err_msg;
extern int32_t xpf_err_code;
#endif

enum XPF_ERR {
    XPF_ERR_NONE,
    XPF_ERR_HELPER_LOAD_FAILED = 1,
    XPF_ERR_CORE_ABNORMAL,
    XPF_ERR_CONFIG_PLUGIN_LOAD_FAILED,
    XPF_ERR_CONFIG_INIT_FAILED,
    XPF_ERR_CONFIG_MISSING,
    XPF_ERR_CONFIG_SERVICE,
    XPF_ERR_APP_IS_ALREADY_RUNNING,
    XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT,
    XPF_ERR_PLUGIN_LOAD_FAILED,
};

QString XPFErrorCode2String(int32_t errcode);

void setXPFErrorCode(int32_t errcode);

}

#endif // XPFGLOBAL_H
