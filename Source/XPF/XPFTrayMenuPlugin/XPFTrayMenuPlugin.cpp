#include "XPFTrayMenuPlugin.h"
#include "TrayIconRClickWgt.h"
#include <XPFTrayMenuTopicDef>
#include <IXPFPluginHelper>
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

using namespace XPFTrayMenu;

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

    g_pPluginHelper->subMessage(this, TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION);
}

void XPFTrayMenuPlugin::initAfterPlugin() {
}

QWidget* XPFTrayMenuPlugin::getWidget(const QString& WID) {
    Q_UNUSED(WID)
    return nullptr;
}

QString XPFTrayMenuPlugin::getPluginName() {
    return "XPFTrayMenuPlugin";
}

void XPFTrayMenuPlugin::release() {
    g_pPluginHelper->unsubMessage(this, TOPIC_XPF_TRAYMENU, MSG_ID_ICON_ACTION);
}

void XPFTrayMenuPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)
    if (topic == TOPIC_XPF_TRAYMENU) {
        switch (msgid) {
        case MSG_ID_ICON_ACTION: {
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
        } break;
        default:
            break;
        }
    }
}
