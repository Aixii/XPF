#include "XPFDbServicePlugin.h"
#include "IXPFPluginHelper.h"

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFDbService4SqlitePlugin::XPFDbService4SqlitePlugin() {
}

XPFDbService4SqlitePlugin::~XPFDbService4SqlitePlugin() {
}

void XPFDbService4SqlitePlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFDbService4SqlitePlugin::initAfterPlugin() {

    g_pPluginHelper->registerService()
}

void XPFDbService4SqlitePlugin::release() {
}

void XPFDbService4SqlitePlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}

QWidget* XPFDbService4SqlitePlugin::getWidget(const QString& WID) {

    return Q_NULLPTR;
}

QString XPFDbService4SqlitePlugin::getPluginName() {
    return "XPFDbServicePlugin";
}
