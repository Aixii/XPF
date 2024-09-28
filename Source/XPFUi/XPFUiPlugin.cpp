#include "XPFUiPlugin.h"
#include "IXPFPluginHelper.h"
#include "XPFUiTool.h"

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFUiPlugin::XPFUiPlugin() {
}

XPFUiPlugin::~XPFUiPlugin() {
}

void XPFUiPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFUiPlugin::initAfterPlugin() {
}

QWidget* XPFUiPlugin::getWidget(const QString& WID) {
    QString path = QString("%0/XPFUi/%1.xml")
                       .arg(g_pPluginHelper->getXPFBinConfigDir())
                       .arg(WID);
    QWidget* widget = XPFUiTool::generateWidget(path);
    return widget;
}

void XPFUiPlugin::release() {
}

void XPFUiPlugin::onMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}
