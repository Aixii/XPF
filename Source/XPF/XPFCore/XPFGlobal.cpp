#define XPFGLOBAL_CPP

#include "XPFCore.h"
#include <QMap>
#include <QString>
#include <QTranslator>
#include <XPFGlobal>

static QMap<int32_t, QString> xpf2string = {
    { XPF::XPF_ERR_CONFIG_MISSING, QObject::tr(u8"配置项缺失或配置文件缺失") },
    { XPF::XPF_ERR_CONFIG_SERVICE, QObject::tr(u8"配置服务未加载") },
    { XPF::XPF_ERR_APP_IS_ALREADY_RUNNING, QObject::tr(u8"软件已经启动了") },
};

namespace XPF {

QString xpf_err_msg;
int32_t xpf_err_code;

QString XPFErrorCode2String(int32_t errcode) {
    return xpf2string.value(errcode);
}

void setXPFErrorCode(int32_t errcode) {
    xpf_err_code = errcode;
    xpf_err_msg  = xpf2string.value(errcode, "");
    if (xpf_err_msg.isEmpty()) {
        xpf_err_msg = QString::number(xpf_err_code, 16);
    }
}

}
