#define XPFGLOBAL_CPP

#include "XPFGlobal.h"
#include <QMap>
#include <QTranslator>
#include <QString>

static QMap<int32_t, QString> xpf2string = {
    {XPF::XPF_ERR_CONFIG_FILE_NOEXISTS,         QObject::tr(u8"XPF.xml 文件不存在")},
    {XPF::XPF_ERR_CONFIG_FILE_OPEN_FAILED,      QObject::tr(u8"XPF.xml 文件打开失败")},
    {XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED,     QObject::tr(u8"XPF.xml 文件解析失败")},
    {XPF::XPF_ERR_CONFIG_NOTAPPNAME,            QObject::tr(u8"XPF.xml 缺少 AppName 配置项")},
    {XPF::XPF_ERR_APP_IS_ALREADY_RUNNING,       QObject::tr(u8"软件已经启动了")},
};

namespace XPF {

QString xpf_err_msg;
int32_t xpf_err_code;

QString XPFErrorCode2String(int32_t errcode)
{
    return xpf2string.value(errcode);
}

void setXPFErrorCode(int32_t errcode)
{
    xpf_err_code = errcode;
    xpf_err_msg = xpf2string.value(errcode, "");
    if(xpf_err_msg.isEmpty())
    {
        xpf_err_msg = QString::number(xpf_err_code, 16);
    }
}

}
