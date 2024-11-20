#define XPFGLOBAL_CPP

#include "XPFCore.h"
#include <QMap>
#include <QString>
#include <QTranslator>
#include <XPFGlobal>


QMap<int32_t, QString> xpf_err_2_string = {
    { XPF::XPF_ERR_HELPER_LOAD_FAILED, QObject::tr(u8"XPF 助手加载失败") },
    { XPF::XPF_ERR_CORE_ABNORMAL, QObject::tr(u8"XPF 核心异常") },
    { XPF::XPF_ERR_CONFIG_PLUGIN_LOAD_FAILED, QObject::tr(u8"XPF 配置插件加载失败") },
    { XPF::XPF_ERR_CONFIG_INIT_FAILED, QObject::tr(u8"初始化配置失败") },
    { XPF::XPF_ERR_CONFIG_MISSING, QObject::tr(u8"配置项缺失或配置文件缺失") },
    { XPF::XPF_ERR_CONFIG_SERVICE, QObject::tr(u8"配置服务错误") },
    { XPF::XPF_ERR_APP_IS_ALREADY_RUNNING, QObject::tr(u8"软件已经启动了") },
    { XPF::XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT, QObject::tr(u8"本地套接字服务创建失败") },
    { XPF::XPF_ERR_PLUGIN_LOAD_FAILED, QObject::tr(u8"插件加载失败") }
};

namespace XPF {

QString xpf_err_msg;
int32_t xpf_err_code;

QString XPFErrorCode2String(int32_t errcode) {
    return xpf_err_2_string.value(errcode);
}

void setXPFErrorCode(int32_t errcode) {
    xpf_err_code = errcode;
    xpf_err_msg  = xpf_err_2_string.value(errcode, "");
    if (xpf_err_msg.isEmpty()) {
        xpf_err_msg = QString::number(xpf_err_code, 16);
    }
}

}
