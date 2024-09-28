#include "XPFConfigsPlugin.h"
#include "IXPFPluginHelper.h"

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFConfigsPlugin::XPFConfigsPlugin() {
}

XPFConfigsPlugin::~XPFConfigsPlugin() {
}

void XPFConfigsPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFConfigsPlugin::initAfterPlugin() {
}

void XPFConfigsPlugin::release() {
}

void XPFConfigsPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}

QWidget* XPFConfigsPlugin::getWidget(const QString& WID) {

    return Q_NULLPTR;
}

QString XPFConfigsPlugin::getPluginName() {

    return QString("XPFConfigs");
}
