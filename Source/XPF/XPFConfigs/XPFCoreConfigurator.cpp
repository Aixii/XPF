#include "XPFCoreConfigurator.h"
#include "XPFConfigExceptionImpl.h"
#include "XPFCoreConfigDef"

#ifndef NDEBUG
#include <QDebug>
#endif

#include <QApplication>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QVariantList>
#include <QWidget>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QRegularExpression>
#else
#include <QRegExp>
#endif

XPFCoreConfigurator::XPFCoreConfigurator(QObject* parent)
    : QObject(parent) { }

XPFCoreConfigurator::~XPFCoreConfigurator() {
}

void XPFCoreConfigurator::init() {
    /* 读配置文件 */
    QDomDocument doc("XPFCoreConfig");

#ifndef NDEBUG
    qDebug() << "Run Path: " << QDir::currentPath();
#endif

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
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            XPFConfigExceptionImpl exp(tr(u8"xpf.xml 文件打开失败"),
                                       XPFConfig::XPF_ERR_CONFIG_FILE_OPEN_FAILED);
            throw exp;
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
            XPFConfigExceptionImpl exp(tr(u8"xpf.xml 解析失败"),
                                       XPFConfig::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
            throw exp;
        }

        QDomElement em = root.firstChildElement("AppName");
        if (em.isNull()) {
            QString appName = em.text();
            if (appName.isEmpty()) {
                XPFConfigExceptionImpl exp(tr(u8"xpf.xml 解析失败"),
                                           XPFConfig::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
                throw exp;
            }
            setConfigItem(CONFIG_XPF_APP_NAME, appName);
        }

        em = root.firstChildElement("MultiStart");

        bool enable = (em.text() == "true");
        setConfigItem(CONFIG_XPF_MULTISTART, enable);

        /* 应用窗体配置 START */
        em = root.firstChildElement("AppScreens");
        if (!em.isNull()) {
            parseScreenXml(em);
        }
        /* 应用窗体配置 END */

        /* 托盘 START */
        em = root.firstChildElement("TrayIcon");
        if (!em.isNull() && em.attribute("enable") == "true") {
            setConfigItem(CONFIG_XPF_TRAYICON_ENABLE, true);
        }
        else {
            setConfigItem(CONFIG_XPF_TRAYICON_ENABLE, false);
        }
        /* 托盘 END */
    }
    while (0);
}

QVariant XPFCoreConfigurator::getConfigItem(const QString& config_key) {
    return m_Configs.value(config_key);
}

void XPFCoreConfigurator::setConfigItem(const QString& config_key, const QVariant& var) {
    m_Configs[config_key] = var;
}

bool XPFCoreConfigurator::parseScreenXml(const QDomElement& em) {
    if (!em.isNull()) {
        QDomNodeList list = em.elementsByTagName("Screen");

        QVariantList varlist;

        for (int index = 0; index < list.size(); index++) {

            QVariantMap map;

            QDomNode node = list.at(index);

            QDomElement element = node.toElement();
            if (element.isNull()) {
                continue;
            }

            QDomElement e = element.firstChildElement("ID");

            if (e.isNull()) {
                continue;
            }
            int base = e.attribute("base").toInt();
            if (base != 16 && base != 8 && base != 2) {
                base = 10;
            }

            bool ok = false;
            int  id = e.text().toUInt(&ok, base);
            if (!ok || id < 0) {
                continue;
            }

            map[CONFIG_XPF_SCREEN_ID] = id;

            if (element.attribute("fullscreen") != "false") {
                map[CONFIG_XPF_SCREEN_ISFULLSCREEN] = true;
            }
            else {
                map[CONFIG_XPF_SCREEN_ISFULLSCREEN] = false;
                QSize   size(0, 0);
                QString sizestr = element.attribute("size");
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                QRegularExpression reg("(\\d+):(\\d+)");

                QRegularExpressionMatch match = reg.match(sizestr);
                if (match.hasMatch()) {
                    QString wstr = match.captured(1);
                    QString hstr = match.captured(2);
#else
                QRegExp reg("(\\d+):(\\d+)");
                if (reg.exactMatch(sizestr)) {
                    QString wstr = reg.cap(1);
                    QString hstr = reg.cap(2);
#endif
                    if (wstr.isEmpty() || hstr.isEmpty()) {
                        map[CONFIG_XPF_SCREEN_ISFULLSCREEN] = true;
                    }
                    else {
                        size.setWidth(wstr.toInt());
                        size.setHeight(hstr.toInt());
                        map[CONFIG_XPF_SCREEN_SIZE] = size;
                    }
                }
                else {
                    map[CONFIG_XPF_SCREEN_ISFULLSCREEN] = true;
                }
            }

            {
                e = element.firstChildElement("Name");

                QString name = e.text();
                if (name.isEmpty()) {
                    name = QString::asprintf("%d", id);
                }
                QString newName = name;

                int counter = 0;
                for (QVariant& var : varlist) {
                    QVariantMap map = var.toMap();
                    if (map[CONFIG_XPF_SCREEN_NAME].toString() == newName) {
                        counter++;
                        newName = QString("%1_%2").arg(name).arg(counter);
                    }
                }
            }

            {
                e = element.firstChildElement("WidgetBody");
                QString widgetName;
                if (!e.isNull()) {
                    widgetName = e.text();
                }
                map[CONFIG_XPF_SCREEN_BODY] = widgetName;
            }
            {
                e = element.firstChildElement("WidgetHeader");

                quint32 height = 0;
                QString widgetName;
                if (!e.isNull()) {
                    widgetName = e.text();
                    height     = e.attribute("height").toUInt();
                    QVariantMap xmap;
                    xmap[CONFIG_XPF_SCREEN_HEADER_NAME]   = widgetName;
                    xmap[CONFIG_XPF_SCREEN_HEADER_HEIGHT] = height;
                    map[CONFIG_XPF_SCREEN_HEADER]         = xmap;
                }
            }
            {
                e = element.firstChildElement("Icon");
                if (!e.isNull()) {
                    QString icon = e.text();
                    if (!icon.isEmpty()) {
                        map[CONFIG_XPF_SCREEN_ICON] = icon;
                    }
                }
            }
            varlist.append(map);
        } // for
        setConfigItem(CONFIG_XPF_SCREEN, varlist);
    }
    return true;
}
