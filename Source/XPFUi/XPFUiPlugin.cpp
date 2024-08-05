#include "XPFUiPlugin.h"
#include "IXPFPluginHelper.h"
#include "XPFUiTool.h"

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFUiPluin::XPFUiPluin() {
}

XPFUiPluin::~XPFUiPluin() {
}

void XPFUiPluin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFUiPluin::initAfterPlugin() {
}

QWidget* XPFUiPluin::getWidget(const QString& WID) {
    QString path = QString("%0/XPFUi/%1.xml")
                       .arg(g_pPluginHelper->getXPFBinConfigDir())
                       .arg(WID);
    QWidget* widget = XPFUiTool::generateWidget(path);
    return widget;
}

void XPFUiPluin::release() {
}

void XPFUiPluin::onMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}
