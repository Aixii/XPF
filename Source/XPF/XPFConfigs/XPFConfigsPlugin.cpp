#include "XPFConfigsPlugin.h"
#include "XPFCoreConfigDef"
#include <IXPFPluginHelper>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFConfigsPlugin::XPFConfigsPlugin()
    : m_ConfigService(nullptr)
    , m_CoreConfigurator(nullptr) {
}

XPFConfigsPlugin::~XPFConfigsPlugin() {

    if (m_ConfigService != nullptr) {
        delete m_ConfigService;
    }
    if (m_CoreConfigurator != nullptr) {
        delete m_CoreConfigurator;
    }
}

void XPFConfigsPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_ConfigService == nullptr) {
        m_ConfigService = new XPFConfigServiceImpl;
        g_pPluginHelper->registerService(IID_IXPFConfigService, m_ConfigService);
    }

    if (m_CoreConfigurator == nullptr) {
        m_CoreConfigurator = new XPFCoreConfigurator;
        m_CoreConfigurator->init();
        m_ConfigService->registerConfigurator(XPF_CORE_CONFIGURATOR_NAME, m_CoreConfigurator);
    }
}

void XPFConfigsPlugin::initAfterPlugin() {
}

void XPFConfigsPlugin::release() {
}

void XPFConfigsPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(topic)
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}

QWidget* XPFConfigsPlugin::getWidget(const QString& WID) {
    Q_UNUSED(WID)
    return Q_NULLPTR;
}

QString XPFConfigsPlugin::getPluginName() {

    return QString("XPFConfigs");
}
