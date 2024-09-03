#include "XPFTrayMenuPlugin.h"
#include "IXPFPluginHelper.h"
#include "TrayIconRClickWgt.h"
#include "XPFDef.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFTrayMenuPlugin::XPFTrayMenuPlugin(QObject* parent)
    : QObject(parent)
    , m_RClickWgt(nullptr) {
}

XPFTrayMenuPlugin::~XPFTrayMenuPlugin() {
}

void XPFTrayMenuPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_RClickWgt == nullptr) {
        m_RClickWgt = new TrayIconRClickWgt;
    }

    g_pPluginHelper->subMessage(this, XPF_MSG_ID_SYS_TRAY_ICON_ACTION);
}

void XPFTrayMenuPlugin::initAfterPlugin() {
}

QWidget* XPFTrayMenuPlugin::getWidget(const QString& WID) {
    Q_UNUSED(WID)
    return nullptr;
}

void XPFTrayMenuPlugin::release() {
    g_pPluginHelper->unsubMessage(this, XPF_MSG_ID_SYS_TRAY_ICON_ACTION);
}

void XPFTrayMenuPlugin::onMessage(uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    if (msgid == XPF_MSG_ID_SYS_TRAY_ICON_ACTION) {
        switch (param.toInt()) {
        case TRAY_ICON_ACTION_RIGHT_CLICKED:
            m_RClickWgt->move(QCursor::pos() - QPoint(0, m_RClickWgt->height()));
            m_RClickWgt->activateWindow();
            m_RClickWgt->setFocus();
            m_RClickWgt->show();
            break;
        default:
            break;
        }
    }
    Q_UNUSED(sender)
}
