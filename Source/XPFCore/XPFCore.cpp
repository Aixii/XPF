#include "XPFCore.h"
#include "XPFGlobal.h"
#include <QDir>
#include <QDomDocument>
#include <QSharedMemory>
#include <QApplication>
#include <QDomElement>
#include <QLocalSocket>
#include <QLocalServer>

const static char *xpf_core_xml_filename = "./XPFConfig/XPF.xml";
const static char *xpf_core_pluginload_xml_filename = "./XPFConfig/XPFLoad.xml";

XPFCore::XPFCore() {

}

bool XPFCore::load() {
    bool ret = false;
    QDomDocument doc("XPFConfig");
    QFile file(QString(xpf_core_xml_filename));
    if(!file.exists())
    {
        XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_NOEXISTS);
        return ret;
    }
    if (!file.open(QIODevice::ReadOnly)){
        XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_OPEN_FAILED);
        return ret;
    }

    QString content = file.readAll();
    if (!doc.setContent(content, false, &content)) {
        XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
        file.close();
        return ret;
    }

    file.close();

    // 获取根元素
    QDomElement root = doc.documentElement();
    if(root.isNull())
    {
        XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
        return ret;
    }
    QDomElement em = root.firstChildElement("AppName");
    if(em.isNull())
    {
        QString appName = em.text();
        if(appName.isEmpty())
        {
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
            return ret;
        }
        m_Config[STR_XPF_APPNAME] = appName;
    }

    em = root.firstChildElement("MultiStart");
    int enable = em.text().toInt();
    if(enable)
    {
        m_Config[STR_XPF_MULTISTART_ENABLE] = true;
    }
    else
    {
        m_Config[STR_XPF_MULTISTART_ENABLE] = false;
        //检测软件是否已运行。
        if(isAlreadyRunning())
        {
            if(XPF::xpf_err_code == 0)
            {
                XPF::setXPFErrorCode(XPF::XPF_ERR_APP_IS_ALREADY_RUNNING);
            }
            return ret;
        }
    }

    // 加载插件
    loadPlugins();

    ret = true;
    return ret;

}

bool XPFCore::isAlreadyRunning()
{
    static const QString serverName = QApplication::applicationName();
    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (socket.waitForConnected(100)) {
        // 如果连接成功，则程序已经在运行
        socket.disconnectFromServer();
        return true;
    }

    // 如果连接失败，则创建本地服务器
    QLocalServer* server = new QLocalServer();
    if (!server->listen(serverName)) {
        XPF::setXPFErrorCode(XPF::XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT);
        delete server;
        return true;
    }

    return false;
}

void XPFCore::loadPlugins()
{
    QDomDocument doc("load_config");
    QFile file(QString(xpf_core_pluginload_xml_filename));
    if(file.exists())
    {
        doc.setContent(file.readAll());
    }
    QDomElement root = doc.documentElement();
}

