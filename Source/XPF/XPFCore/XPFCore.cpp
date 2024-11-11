#include "XPFCore.h"
#include "XPFPluginHelperImpl.h"

#include <IXPFConfigException>
#include <XPFCoreTopicDef>
#include <XPFGlobal>
#include <XPFTrayMenuTopicDef>
#include <XPFUiTopicDef>

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QHBoxLayout>
#include <QLocalServer>
#include <QLocalSocket>
#include <QMenu>
#include <QMessageBox>
#include <QPluginLoader>
#include <QScreen>
#include <QSharedMemory>
#include <QSystemTrayIcon>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QRegularExpression>
#include <QScreen>
#else
#include <QDesktopWidget>
#include <QRegExp>
#endif

const static char* xpf_core_xml_filename            = "XPFConfig/XPF.xml";
const static char* xpf_core_pluginload_xml_filename = "XPFConfig/XPFPlugins.xml";

XPFCore* xpf_core = nullptr;

XPFCore::XPFCore(QObject* parent)
    : QObject(parent)
    , m_XPFHelper(new XPFPluginHelperImpl)
    , m_LocalServer(nullptr)
    , m_TrayIcon(nullptr) {

    xpf_core = this;
}

XPFCore::~XPFCore() {
    //    XPFPluginHelperImpl* helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);
    //    for (QWidget* widget : helper->getXPFScreenWidgets()) {
    //        delete widget;
    //    }

    if (m_LocalServer != nullptr) {
        m_LocalServer->close();
        delete m_LocalServer;
    }

    if (m_TrayIcon != nullptr) {
        delete m_TrayIcon;
        m_TrayIcon = nullptr;
    }

    for (IXPFPlugin* plugin : m_PluginsSort) {
        m_XPFHelper->unsubMessage(plugin);
        plugin->release();
        unloadPlugin(plugin->getPluginName());
    }
}

bool XPFCore::load(const QString& fileName) {
    bool ret = false;

    do {
        /* 读配置文件 */
        QDomDocument doc("XPFCoreConfig");

        qDebug() << QDir::currentPath();

        QFile file(fileName);
        if (!file.exists()) {
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_NOEXISTS);
            break;
        }
        if (!file.open(QIODevice::ReadOnly)) {
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_OPEN_FAILED);
            break;
        }

        QString content = file.readAll();

        if (!doc.setContent(content, false, &content)) {
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
            file.close();
            break;
        }

        file.close();

        // 获取根元素
        QDomElement root = doc.documentElement();
        if (root.isNull()) {
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
            break;
        }

        /* 获取AppName并检查是否多次启动 START */
        QDomElement em = root.firstChildElement("AppName");
        if (em.isNull()) {
            QString appName = em.text();
            if (appName.isEmpty()) {
                XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_FILE_PARSE_FAILED);
                break;
            }
            m_Config[STR_XPF_APPNAME] = appName;
        }

        em = root.firstChildElement("MultiStart");

        bool enable = (em.text() == "true");
        if (enable) {
            m_Config[STR_XPF_MULTISTART_ENABLE] = true;
        }
        else {
            m_Config[STR_XPF_MULTISTART_ENABLE] = false;
            // 检测软件是否已运行。
            if (isAlreadyRunning()) {
                if (XPF::xpf_err_code == 0) {
                    XPF::setXPFErrorCode(XPF::XPF_ERR_APP_IS_ALREADY_RUNNING);
                }
                break;
            }
        }
        /* 获取AppName并检查是否多次启动 END */

        /* 应用窗体配置 START */
        em = root.firstChildElement("AppScreens");
        if (!em.isNull()) {
            parseScreenXml(em);
        }
        /* 应用窗体配置 END */

        /* 托盘 START */
        em = root.firstChildElement("TrayIcon");
        if (!em.isNull() && em.attribute("enable") == "true") {
            if (!QSystemTrayIcon::isSystemTrayAvailable()) {
                QMessageBox::warning(nullptr, u8"警告", u8"创建系统托盘失败，当前系统不支持托盘图标");
            }
            else {
                m_TrayIcon = new QSystemTrayIcon(this);

                m_TrayIcon->setIcon(QIcon("./XPFResources/x.png"));
                m_TrayIcon->setToolTip(m_Config.value(STR_XPF_APPNAME, "XPF").toString());
                m_TrayIcon->show();
            }
        }
        /* 托盘 END */

        ret = true;
    }
    while (0);

    return ret;
}

void XPFCore::reloadPlugin(const QString& pluginName) {
    QPluginLoader* loader = m_PluginLoaders.value(pluginName, nullptr);
    if (loader == nullptr) {
        return;
    }
    IXPFPlugin* plugin = qobject_cast<IXPFPlugin*>(loader->instance());
    if (plugin != nullptr) {
        m_Plugins[pluginName] = plugin;
    }
}

void XPFCore::unloadPlugin(const QString& pluginName) {
    QPluginLoader* loader = m_PluginLoaders.value(pluginName, nullptr);
    if (loader == nullptr) {
        return;
    }
    loader->unload();
    m_Plugins.remove(pluginName);
}

void XPFCore::showScreens() {
    XPFPluginHelperImpl* helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);
    for (QWidget* widget : helper->getXPFScreenWidgets()) {
        widget->show();
    }
}
void XPFCore::quitApp() {
    emit sigQuitApp();
}

bool XPFCore::initialize() {

#if defined(_WIN32)
#ifdef QT_NO_DEBUG
    QPluginLoader* loader = new QPluginLoader(QString("XPFPlugins/XPFConfigsPlugin.dll"));
#else
    QPluginLoader* loader = new QPluginLoader(QString("XPFPlugins/XPFConfigsPlugind.dll"));
#endif
#elif defined(UNIX)
#ifdef QT_NO_DEBUG
    QPluginLoader* loader = new QPluginLoader(QString("XPFPlugins/XPFConfigsPlugin.so"));
#else
    QPluginLoader* loader = new QPluginLoader(QString("XPFPlugins/XPFConfigsPlugind.so"));
#endif
#endif
    QObject* obj = loader->instance();
    if (obj) {
        IXPFPlugin* plugin = qobject_cast<IXPFPlugin*>(obj);
        if (plugin != nullptr) {
            QString plugin_name          = plugin->getPluginName();
            m_Plugins[plugin_name]       = plugin;
            m_PluginLoaders[plugin_name] = loader;
            m_PluginsSort.append(plugin);
            try {
                plugin->initPlugin(m_XPFHelper);
            }
            catch (IXPFConfigException& e) {
                QMessageBox::critical(nullptr, u8"错误", QString::fromStdString(std::string(e.what())));
                return false;
            }
        }
        else {
            QMessageBox::critical(nullptr,
                                  u8"错误",
                                  QString(u8"无法加载 %1 E0000001").arg("XPFConfigPlugin"));
            return false;
        }
    }
    else {
        QMessageBox::critical(nullptr,
                              u8"错误",
                              QString(u8"无法加载 %1 E0000002 %2").arg("XPFConfigPlugin").arg(loader->errorString()));
        return false;
    }

    if (!load(QString::fromUtf8(xpf_core_xml_filename))) {
        QMessageBox::critical(nullptr, QObject::tr(u8"错误"), XPF::xpf_err_msg, QMessageBox::Close);
        return false;
    }

    // 加载插件
    loadPlugins();

    // 加载完成之后，遍历插件执行生命周期函数
    for (IXPFPlugin* plugin : qAsConst(m_PluginsSort)) {
        qDebug() << plugin->getPluginName() + QString(": initAfter invoke.");
        plugin->initAfterPlugin();
    }

    // 初始化界面
    XPFPluginHelperImpl* helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);
    for (QWidget* widget : helper->getXPFScreenWidgets()) {
        QLayout* layout = new QVBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);

        if (!widget->property("Header").toString().isEmpty()) {
            QWidget* cwhead = helper->getXPFWidgetByPlugin("XPFUi", widget->property("Header").toString());
            if (cwhead != nullptr) {
                quint32 headerh = widget->property("HeaderHeight").toUInt();
                cwhead->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                cwhead->setFixedHeight(headerh);
                layout->addWidget(cwhead);
            }
            else {
                widget->setWindowFlags(widget->windowFlags() & ~Qt::FramelessWindowHint);
            }
        }
        QString str = widget->property("Body").toString();
        if (!widget->property("Body").toString().isEmpty()) {
            QString  str    = widget->property("Body").toString();
            QWidget* cwbody = helper->getXPFWidgetByPlugin("XPFUi", widget->property("Body").toString());
            if (cwbody != nullptr) {
                layout->addWidget(cwbody);
            }
        }
    }

    // 托盘基础菜单
    if (m_TrayIcon != nullptr) {
        using namespace XPFTrayMenu;
        auto func = [this](QSystemTrayIcon::ActivationReason reason) {
            switch (reason) {
            // 左键
            case QSystemTrayIcon::Trigger:
                m_XPFHelper->sendSyncMessage(TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION, TRAY_ICON_ACTION_LEFT_CLICKED);
                break;
            // 右键单击
            case QSystemTrayIcon::Context:
                m_XPFHelper->sendSyncMessage(TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION, TRAY_ICON_ACTION_RIGHT_CLICKED);
                break;
            // 双击
            case QSystemTrayIcon::DoubleClick:
                m_XPFHelper->sendSyncMessage(TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION, TRAY_ICON_ACTION_DOUBLE_CLICKED);
                break;
            // 中键单击
            case QSystemTrayIcon::MiddleClick:
                m_XPFHelper->sendSyncMessage(TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION, TRAY_ICON_ACTION_MIDDLE_CLICKED);
                break;
            default:
                break;
            }
        };
        QObject::connect(m_TrayIcon, &QSystemTrayIcon::activated, this, func, Qt::UniqueConnection);
    }
    return true;
}

IXPFPlugin* XPFCore::getPlugin(const QString& name) {
    return m_Plugins.value(name, nullptr);
}

bool XPFCore::isAlreadyRunning() {
    static const QString serverName = QApplication::applicationName();

    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (socket.waitForConnected(100)) {
        // 如果连接成功，则程序已经在运行
        socket.disconnectFromServer();
        return true;
    }

    // 如果连接失败，则创建本地服务器
    if (m_LocalServer == nullptr) {
        m_LocalServer = new QLocalServer();
    }
    if (!m_LocalServer->listen(serverName)) {
        XPF::setXPFErrorCode(XPF::XPF_ERR_LOCAL_SOCKET_SERVER_CANNOT_CREAT);
        delete m_LocalServer;
        return true;
    }
    return false;
}

bool XPFCore::parseScreenXml(const QDomElement& em) {
    auto setFullScreen = [](QWidget* widget) {
        widget->showMaximized();
        widget->setWindowState(Qt::WindowMaximized);
    };

    if (!em.isNull()) {
        QDomNodeList list = em.elementsByTagName("Screen");

        int screenCount = 0;
        if (list.size() >= 0) {
            screenCount = QApplication::screens().size();
        }
        int desktopIndex = 0;
        for (int index = 0; index < list.size(); index++, desktopIndex++) {
            QDomNode node = list.at(index);

            QDomElement element = node.toElement();
            if (element.isNull()) {
                continue;
            }

            if (index >= screenCount) {
                desktopIndex = 0;
            }

            QRect rect = QApplication::screens().at(desktopIndex)->availableGeometry();
            {
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

                QWidget* widget = m_XPFHelper->getXPFScreenWidget(id);
                if (widget != nullptr) {
                    return false;
                }

                widget = new QWidget;
                widget->hide();
                widget->setContentsMargins(0, 0, 0, 0);
                widget->setWindowFlags(Qt::FramelessWindowHint);
                widget->setProperty("ID", id);

                XPFPluginHelperImpl* helper = dynamic_cast<XPFPluginHelperImpl*>(m_XPFHelper);

                if (element.attribute("fullscreen") != "false") {
                    widget->setGeometry(rect);
                    setFullScreen(widget);
                }
                else {
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
                            widget->setGeometry(rect);
                            setFullScreen(widget);
                        }
                        else {
                            size.setWidth(wstr.toInt());
                            size.setHeight(hstr.toInt());
                            int x = rect.left();
                            int y = rect.top();
                            if (size.width() < rect.width()) {
                                x += (rect.width() - size.width()) / 2;
                            }
                            if (size.height() < rect.height()) {
                                y += (rect.height() - size.height()) / 2;
                            }
                            widget->setGeometry(x, y, size.width(), size.height());
                            widget->setFixedSize(size);
                            widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                        }
                    }
                    else {
                        widget->setGeometry(rect);
                        setFullScreen(widget);
                    }
                }

                {
                    e = element.firstChildElement("Name");

                    QString name = e.text();
                    if (name.isEmpty()) {
                        name = QString::asprintf("%d", id);
                    }
                    QString newName = name;

                    QList<QWidget*> sws = helper->getXPFScreenWidgets();

                    int counter = 0;
                    for (QWidget* w : sws) {
                        if (w->objectName() == newName) {
                            counter++;
                            newName = QString("%1_%2").arg(name).arg(counter);
                        }
                    }
                    widget->setObjectName(newName);
                    widget->setWindowTitle(newName);
                }
                helper->setXPFScreenWidget(id, widget);

                {
                    e = element.firstChildElement("WidgetBody");
                    QString widgetName;
                    if (!e.isNull()) {
                        widgetName = e.text();
                    }
                    widget->setProperty("Body", widgetName);
                }
                {
                    e = element.firstChildElement("WidgetHeader");

                    quint32 height = 0;

                    QString widgetName;
                    if (!e.isNull()) {
                        widgetName = e.text();
                        height     = e.attribute("height").toUInt();
                    }
                    else {
                        widget->setWindowFlags(widget->windowFlags() & ~Qt::FramelessWindowHint);
                    }
                    widget->setProperty("Header", widgetName);
                    widget->setProperty("HeaderHeight", height);
                }
                {
                    e = element.firstChildElement("Icon");

                    if (!e.isNull()) {
                        QString icon = e.text();
                        if (!icon.isEmpty()) {
                            QString appDir   = QApplication::applicationDirPath();
                            QString iconPath = appDir + QString("/XPFResource/%0").arg(icon);
                            widget->setWindowIcon(QIcon(iconPath));
                        }
                    }
                }
            }
        }
    }
    return true;
}

void XPFCore::loadPlugins() {
    QDomDocument doc("load_config");

    QFile file(QString::fromUtf8(xpf_core_pluginload_xml_filename));
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        doc.setContent(file.readAll());
        file.close();
    }
    else {
        return;
    }
    QDomElement root       = doc.documentElement();
    QDomElement plugins_em = root.firstChildElement("Plugins");
    QDomElement plugin_em  = plugins_em.firstChildElement("Plugin");

    while (!plugin_em.isNull()) {
        QString plugin_lib = plugin_em.attribute("plugin_lib");
        QString plugin_dir = plugin_em.attribute("plugin_dir");

        int enable = plugin_em.attribute("enable").toInt();

#if defined(_WIN32)
#ifdef QT_NO_DEBUG
        QPluginLoader* loader = new QPluginLoader(QString("%0/%1.dll").arg(plugin_dir).arg(plugin_lib));
#else
        QPluginLoader* loader = new QPluginLoader(QString("%0/%1d.dll").arg(plugin_dir).arg(plugin_lib));
#endif
#elif defined(UNIX)
#ifdef QT_NO_DEBUG
        QPluginLoader* loader = new QPluginLoader(QString("%0/%1.so").arg(plugin_dir).arg(plugin_lib));
#else
        QPluginLoader* loader = new QPluginLoader(QString("%0/%1d.so").arg(plugin_dir).arg(plugin_lib));
#endif
#endif
        QObject* obj = loader->instance();
        if (obj) {
            IXPFPlugin* plugin = qobject_cast<IXPFPlugin*>(obj);
            if (plugin != nullptr) {
                if (enable == 0) {
                    loader->unload();
                }
                else {
                    QString plugin_name          = plugin->getPluginName();
                    m_Plugins[plugin_name]       = plugin;
                    m_PluginLoaders[plugin_name] = loader;
                    m_PluginsSort.append(plugin);
                    plugin->initPlugin(m_XPFHelper);
                }
            }
            else {
                QMessageBox::critical(nullptr,
                                      u8"错误",
                                      QString(u8"无法加载 %1 E0000001").arg(plugin_lib));
            }
        }
        else {
            QMessageBox::critical(nullptr,
                                  u8"错误",
                                  QString(u8"无法加载 %1 E0000002 %2").arg(plugin_lib).arg(loader->errorString()));
        }
        plugin_em = plugin_em.nextSiblingElement("Plugin");
    }
}
