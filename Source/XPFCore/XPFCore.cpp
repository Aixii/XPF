#include "XPFCore.h"
#include "XPFGlobal.h"
#include "XPFPluginHelperImpl.h"
#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <QSharedMemory>
#include <QApplication>
#include <QDomElement>
#include <QLocalSocket>
#include <QLocalServer>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDesktopWidget>

const static char *xpf_core_xml_filename = "./XPFConfig/XPF.xml";
const static char *xpf_core_pluginload_xml_filename = "./XPFConfig/XPFPlugins.xml";

XPFCore::XPFCore()
    : m_LocalServer(nullptr)
{
    m_XPFHelper = new XPFPluginHelperImpl;
}

XPFCore::~XPFCore()
{
    if(m_LocalServer != nullptr)
    {
        m_LocalServer->close();
        delete m_LocalServer;
    }
}

bool XPFCore::load() {
    bool ret = false;
    QDomDocument doc("XPFConfig");
    QFile file(QString::fromUtf8(xpf_core_xml_filename));
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

    em = root.firstChildElement("AppScreens");
    if(!em.isNull())
    {
        parseScreenXml(em);
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

void XPFCore::showScreens()
{
    XPFPluginHelperImpl *helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);
    for(QWidget *widget : helper->getScreens())
    {
        widget->show();
    }
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
    if(m_LocalServer == nullptr)
    {
        m_LocalServer = new QLocalServer();
    }
    if (!m_LocalServer->listen(serverName)) {
        XPF::setXPFErrorCode(XPF::XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT);
        delete m_LocalServer;
        return true;
    }

    return false;
}

bool XPFCore::parseScreenXml(const QDomElement &em)
{
    if(!em.isNull())
    {
        QDomNodeList list = em.elementsByTagName("Screen");
        int screenCount;
        if(list.size() >= 0)
        {
            screenCount = QApplication::desktop()->screenCount();
        }
        int desktopIndex = 0;
        for(int index = 0; index < list.size(); index++, desktopIndex++)
        {
            QDomNode node = list.at(index);
            QDomElement element = node.toElement();
            if(element.isNull())
            {
                continue;
            }

            if(index >= screenCount)
            {
                desktopIndex = 0;
            }
            QRect rect = QApplication::desktop()->screenGeometry(desktopIndex);
            {
                QDomElement e = element.firstChildElement("id");

                if(e.isNull() )
                {
                    continue;
                }
                bool ok = false;
                int id = e.text().toUInt(&ok);
                if(!ok || id < 0)
                {
                    continue;
                }
                QWidget *widget = new QWidget;
                XPFPluginHelperImpl *helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);
                helper->setXPFScreenWidget(id, widget);

                QSize size(640, 480);
                e = element.firstChildElement("size");
                if(!e.isNull())
                {
                    QDomElement we = e.firstChildElement("width");
                    if(!we.isNull())
                    {
                        int width = we.text().toInt();
                        size.setWidth(width == 0 ? 640 : width);
                    }
                    QDomElement he = e.firstChildElement("height");
                    if(!he.isNull())
                    {
                        int height = he.text().toInt();
                        size.setHeight(height == 0 ? 480 : height);
                    }
                }
                int x = rect.left();
                int y = rect.top();
                if(size.width() < rect.width())
                {
                    x += (rect.width() - size.width()) / 2;
                }
                if(size.height() < rect.height())
                {
                    y += (rect.height() - size.height()) / 2;
                }
                widget->setGeometry(x, y, size.width(), size.height());

                widget->hide();
            }
        }
    }
    return true;
}

void XPFCore::loadPlugins()
{
    QDomDocument doc("load_config");
    QFile file(QString::fromUtf8(xpf_core_pluginload_xml_filename));
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        doc.setContent(file.readAll());
        file.close();
    }
    else
    {
        return;
    }
    QDomElement root = doc.documentElement();

    QDomNodeList list = root.elementsByTagName("plugin");

    for(int index = 0; index < list.size(); index++)
    {
        QDomNode node = list.at(index);
        QDomElement em = node.toElement();
        QString plugin_name = em.attribute("plugin_name");
        QString plugin_lib = em.attribute("plugin_lib");
        int enable = em.attribute("enable").toInt();
        QPluginLoader loader(QString("./XPFPlugins/%0").arg(plugin_lib));
        QObject *obj = loader.instance();
        if(obj)
        {
            IXPFPlugin *plugin = qobject_cast<IXPFPlugin*>(obj);
            if(plugin && enable == 1)
            {
                m_Plugins[plugin_name] = plugin;
                plugin->initPlugin(m_XPFHelper);
            }
            else
            {
                QMessageBox::critical(nullptr, u8"错误", QString(u8"无法加载%1").arg(plugin_lib));
            }
        }

    }
}

