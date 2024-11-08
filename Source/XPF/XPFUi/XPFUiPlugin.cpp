#include "XPFUiPlugin.h"
#include "XPFUiTool.h"
#include <IXPFPluginHelper>
#include <XPFUiTopicDef>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

XPFUiPlugin::XPFUiPlugin() {
}

XPFUiPlugin::~XPFUiPlugin() {
}

void XPFUiPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;
}

void XPFUiPlugin::initAfterPlugin() {

    g_pPluginHelper->subMessage(this, TOPIC_XPF_UI, XPFUi::HIDE_POPUP_ID);
    g_pPluginHelper->subMessage(this, TOPIC_XPF_UI, XPFUi::SHOW_POPUP_ID);
}

QWidget* XPFUiPlugin::getWidget(const QString& WID) {
    QString path = QString("%0/XPFUi/%1.xml")
                       .arg(g_pPluginHelper->getXPFBinConfigDir())
                       .arg(WID);
    QWidget* widget = XPFUiTool::generateWidget(path);
    return widget;
}

QString XPFUiPlugin::getPluginName() {
    return QString("XPFUi");
}

void XPFUiPlugin::release() {
    g_pPluginHelper->unsubMessage(this, TOPIC_XPF_UI, XPFUi::HIDE_POPUP_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_XPF_UI, XPFUi::SHOW_POPUP_ID);
}

void XPFUiPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)
    if (topic == TOPIC_XPF_UI) {
        switch (msgid) {
        case XPFUi::SHOW_POPUP_ID: {
            QVariantMap map = param.toMap();

            int     screenID = map.value("screenID").toInt();
            QString widgetID = map.value("widgetID").toString();

            QDialog* dialog = dynamic_cast<QDialog*>(g_pPluginHelper->getXPFWidgetById(screenID, widgetID));
            if (dialog != nullptr) {
                dialog->show();
            }
        } break;
        case XPFUi::HIDE_POPUP_ID: {
            QVariantMap map = param.toMap();

            int     screenID = map.value("screenID").toInt();
            QString widgetID = map.value("widgetID").toString();

            QDialog* dialog = dynamic_cast<QDialog*>(g_pPluginHelper->getXPFWidgetById(screenID, widgetID));
            if (dialog != nullptr) {
                dialog->hide();
            }
        } break;
        default:
            break;
        }
    }
}
