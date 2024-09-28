#include "XPFLoginPlugin.h"
#include "IXPFPluginHelper.h"

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFLoginPlugin::XPFLoginPlugin() {
}

XPFLoginPlugin::~XPFLoginPlugin() {
}

void XPFLoginPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFLoginPlugin::initAfterPlugin() {
}

QWidget* XPFLoginPlugin::getWidget(const QString& WID) {

    return Q_NULLPTR;
}

QString XPFLoginPlugin::getPluginName() {
}

void XPFLoginPlugin::release() {
}

void XPFLoginPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}
