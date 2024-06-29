#include "XPFPluginHelperImpl.h"
#include <QFileInfo>



QString XPFPluginHelperImpl::getXPFBinDir()
{
    QFileInfo file(".");
    QString path = file.absoluteFilePath();
    return path;
}

QString XPFPluginHelperImpl::getXPFBinConfigDir()
{
    QFileInfo file("./XPFConfig");
    QString path = file.absoluteFilePath();
    return path;
}

void XPFPluginHelperImpl::subMessage(IXPFPlugin *plugin, uint32_t msgid)
{

}

void XPFPluginHelperImpl::unsubMessage(IXPFPlugin *plugin, uint32_t msgid)
{

}

void XPFPluginHelperImpl::pubMessage(uint32_t msgid, const QVariant &param)
{

}
