#include "XPFCore.h"

#include <IXPFConfigException>
#include <IXPFConfigService>
#include <XPFCoreConfigDef>
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

const static char* xpf_core_pluginload_xml_filename = "XPFConfig/XPFPlugins.xml";

XPFCore::XPFCore(QObject* parent)
    : QObject(parent)
    , m_LocalServer(nullptr)
    , m_TrayIcon(nullptr) {

    m_XPFHelper = XPF::GetXPFPluginHelper();
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

bool XPFCore::initialize() {

    // 首先将自己注册进去
    registerPlugin(this);

    // 加载配置插件
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

    // 加载配置组件
    QObject* obj = loader->instance();
    if (obj) {
        IXPFPlugin* plugin = qobject_cast<IXPFPlugin*>(obj);
        if (plugin != nullptr) {
            QString plugin_name = plugin->getPluginName();

            // 注册组件
            registerPlugin(plugin);

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

    if (!load()) {
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
    IXPFPluginHelper* helper = XPF::GetXPFPluginHelper();

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

bool XPFCore::load() {
    bool ret = false;

    do {
        /* 获取配置服务 */
        IXPFConfigService* config_service = dynamic_cast<IXPFConfigService*>(m_XPFHelper->getService(IID_IXPFConfigService));
        if (config_service == nullptr) {
            qCritical() << tr(u8"未注册配置服务");
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_SERVICE);
            break;
        }

        IXPFConfigurator* configurator = config_service->getConfigurator(XPF_CORE_CONFIGURATOR_NAME);
        if (configurator == nullptr) {
            qCritical() << tr(u8"未注册核心配置器");
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_MISSING);
            break;
        }

        /* 获取AppName并检查是否多次启动 START */
        QString appName = configurator->getConfigItem(CONFIG_XPF_APP_NAME).toString();
        if (appName.isEmpty()) {
            qCritical() << tr(u8"未配置应用名称");
            XPF::setXPFErrorCode(XPF::XPF_ERR_CONFIG_MISSING);
            break;
        }

        bool enable = configurator->getConfigItem(CONFIG_XPF_MULTISTART).toBool();

        if (!enable) {
            // 检测软件是否已运行。
            if (isAlreadyRunning()) {
                if (XPF::xpf_err_code == 0) {
                    qCritical() << tr(u8"应用已经启动");
                    XPF::setXPFErrorCode(XPF::XPF_ERR_APP_IS_ALREADY_RUNNING);
                }
                break;
            }
        }
        /* 获取AppName并检查是否多次启动 END */

        /* 应用窗体配置 START */

        do {

            auto setFullScreen = [](QWidget* widget) {
                widget->showMaximized();
                widget->setWindowState(Qt::WindowMaximized);
            };

            QVariantList varlist = configurator->getConfigItem(CONFIG_XPF_SCREEN).toList();

            int screenCount = 0;
            if (varlist.size() >= 0) {
                screenCount = QApplication::screens().size();
            }
            int desktopIndex = 0;

            for (int index = 0; index < varlist.size(); index++, desktopIndex++) {
                QVariantMap map = varlist.value(index).toMap();

                if (index >= screenCount) {
                    desktopIndex = 0;
                }

                QRect rect = QApplication::screens().at(desktopIndex)->availableGeometry();

                int screen_id = map[CONFIG_XPF_SCREEN_NUMBER].toInt();

                QWidget* widget = m_XPFHelper->getXPFScreenWidget(screen_id);
                if (widget != nullptr) {
                    continue;
                }

                widget = new QWidget;
                widget->hide();
                widget->setContentsMargins(0, 0, 0, 0);
                widget->setWindowFlags(Qt::FramelessWindowHint);
                widget->setProperty("ID", screen_id);

                bool is_fullscreen = map.value(CONFIG_XPF_SCREEN_ISFULLSCREEN, true).toBool();

                if (is_fullscreen) {
                    widget->setGeometry(rect);
                    setFullScreen(widget);
                }
                else {
                    QSize size = map.value(CONFIG_XPF_SCREEN_SIZE, QSize(0, 0)).toSize();
                    if (size.width() == 0 || size.height() == 0) {
                        widget->setGeometry(rect);
                        setFullScreen(widget);
                    }
                    else {
                        size.setWidth(size.width());
                        size.setHeight(size.height());
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
                {

                    QString name = map[CONFIG_XPF_SCREEN_NAME].toString();
                    if (name.isEmpty()) {
                        name = QString::asprintf("%d", screen_id);
                    }

                    widget->setObjectName(name);
                    widget->setWindowTitle(name);
                }

                m_XPFHelper->registerScreenWidget(widget, this);

                {
                    QString widgetName = map[CONFIG_XPF_SCREEN_BODY].toString();
                    widget->setProperty("Body", widgetName);
                }
                {
                    QVariantMap xmap = map[CONFIG_XPF_SCREEN_HEADER].toMap();

                    quint32 height = xmap[CONFIG_XPF_SCREEN_HEADER_HEIGHT].toUInt();

                    QString widgetName = xmap[CONFIG_XPF_SCREEN_HEADER_NAME].toString();

                    if (!widgetName.isEmpty()) {
                        widget->setWindowFlags(widget->windowFlags() & ~Qt::FramelessWindowHint);
                    }

                    widget->setProperty("Header", widgetName);
                    widget->setProperty("HeaderHeight", height);
                }

                {
                    QString icon = map[CONFIG_XPF_SCREEN_ICON].toString();
                    if (!icon.isEmpty()) {
                        QString appDir   = QApplication::applicationDirPath();
                        QString iconPath = appDir + QString("/xpfresource/%0").arg(icon);
                        widget->setWindowIcon(QIcon(iconPath));
                    }
                }
            }
        }
        while (0);
        /* 应用窗体配置 END */
        /* 托盘 START */
        bool trayicon_enable = configurator->getConfigItem(CONFIG_XPF_TRAYICON_ENABLE).toBool();
        if (trayicon_enable) {
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
        m_XPFHelper->registerPlugin(plugin, this);
    }
}

void XPFCore::unloadPlugin(const QString& pluginName) {
    QPluginLoader* loader = m_PluginLoaders.value(pluginName, nullptr);
    if (loader == nullptr) {
        return;
    }
    IXPFPlugin* plugin = m_XPFHelper->getPlugin(pluginName);
    m_XPFHelper->unregisterPlugin(plugin, this);

    loader->unload();
}

void XPFCore::registerPlugin(IXPFPlugin* plugin) {
    m_XPFHelper->registerPlugin(plugin, dynamic_cast<IXPFPlugin*>(this));
}

void XPFCore::unregisterPlugin(IXPFPlugin* plugin) {
    m_XPFHelper->unregisterPlugin(plugin, dynamic_cast<IXPFPlugin*>(this));
}

void XPFCore::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(param)
    Q_UNUSED(sender)
    if (topic == TOPIC_XPF_CORE && msgid == XPFCore_NameSpace::MSG_ID_QUIT_APP) {
        // TODO 退出
    }
}

void XPFCore::showScreens() {
    for (QWidget* widget : m_XPFHelper->getXPFScreenWidgets()) {
        widget->show();
    }
}
void XPFCore::quitApp() {
    emit sigQuitApp();
}

IXPFPlugin* XPFCore::getPlugin(const QString& name) {
    return m_XPFHelper->getPlugin(name);
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
                    QString plugin_name = plugin->getPluginName();

                    registerPlugin(plugin);

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
