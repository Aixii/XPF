#include "XPFCoreConfigurator.h"
#include <QDir>
#include <QDomDocument>
#include <QFile>

#include "XPFConfigExceptionImpl.h"
#include "XPFCoreConfigDef"

XPFCoreConfigurator::XPFCoreConfigurator(QObject* parent)
    : QObject { parent } { }

XPFCoreConfigurator::~XPFCoreConfigurator() {
}

void XPFCoreConfigurator::init() {
    /* 读配置文件 */
    QDomDocument doc("XPFCoreConfig");

    qDebug() << QDir::currentPath();

    do {
        // QFile file("XPF.xml");
        QString filename = "XPF.xml";
        if (!QFile::exists(filename)) {
            filename = "xpf.xml";
        }

        if (!QFile::exists(filename)) {
            filename = "XPFConfig/XPF.xml";
        }

        if (!QFile::exists(filename)) {
            filename = "XPFConfig/xpf.xml";
        }

        if (!QFile::exists(filename)) {
            XPFConfigExceptionImpl exp(tr(u8"xpf.xml 不存在"),
                                       XPFConfig::XPF_ERR_CONFIG_FILE_NOEXISTS);
            throw exp;
            break;
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            XPFConfigExceptionImpl exp(tr(u8"xpf.xml 文件打开失败"),
                                       XPFConfig::XPF_ERR_CONFIG_FILE_OPEN_FAILED);
            throw exp;
            break;
        }

        QString content = file.readAll();

        if (!doc.setContent(content, false, &content)) {
            file.close();
            break;
        }

        file.close();

        // 获取根元素
        QDomElement root = doc.documentElement();
        if (root.isNull()) {
            // XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
            break;
        }

        /* 获取AppName并检查是否多次启动 START */
        QDomElement em = root.firstChildElement("AppName");
        if (em.isNull()) {
            QString appName = em.text();
            if (appName.isEmpty()) {
                // XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
                break;
            }
            // m_Config[STR_XPF_APPNAME] = appName;
        }

        em = root.firstChildElement("MultiStart");

        bool enable = (em.text() == "true");
        if (enable) {
            // m_Config[STR_XPF_MULTISTART_ENABLE] = true;
        }
        else {
            // m_Config[STR_XPF_MULTISTART_ENABLE] = false;
            // 检测软件是否已运行。
            // if (isAlreadyRunning()) {
            //     if (XPF::xpf_err_code == 0) {
            //         XPF::setXPFErrorCode(XPF::XPF_ERR_APP_IS_ALREADY_RUNNING);
            //     }
            //     break;
            // }
        }
        /* 获取AppName并检查是否多次启动 END */

        /* 应用窗体配置 START */
        em = root.firstChildElement("AppScreens");
        if (!em.isNull()) {
            // parseScreenXml(em);
        }
        /* 应用窗体配置 END */

        /* 托盘 START */
        em = root.firstChildElement("TrayIcon");
        if (!em.isNull() && em.attribute("enable") == "true") {
            // if (!QSystemTrayIcon::isSystemTrayAvailable()) {
            //     QMessageBox::warning(nullptr, u8"警告", u8"创建系统托盘失败，当前系统不支持托盘图标");
            // }
            // else {
            //     m_TrayIcon = new QSystemTrayIcon(this);

            //     m_TrayIcon->setIcon(QIcon("./XPFResources/x.png"));
            //     m_TrayIcon->setToolTip(m_Config.value(STR_XPF_APPNAME, "XPF").toString());
            //     m_TrayIcon->show();
            // }
        }
        /* 托盘 END */

        // ret = true;
    }
    while (0);
}

QVariant XPFCoreConfigurator::getConfigItem(const QString& config_key) {
    return m_Configs.value(config_key);
}

void XPFCoreConfigurator::setConfigItem(const QString& config_key, const QVariant& var) {
    m_Configs[config_key] = var;
}
