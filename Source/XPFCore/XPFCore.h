#ifndef XPFCORE_H
#define XPFCORE_H

#include "IXPFPlugin.h"
#include <QMap>
#include <QLibrary>
#include <QVariant>

#define STR_XPF_APPNAME             "AppName"
#define STR_XPF_MULTISTART_ENABLE   "MultiStart"

class XPFCore
{
public:
    XPFCore();
    bool load();

private:
    bool isAlreadyRunning();

private:
    // 应用配置
    QVariantMap m_Config;
    // 所有的插件
    QMap<QString, IXPFPlugin*> m_Plugins;
};

#endif // XPFCORE_H
