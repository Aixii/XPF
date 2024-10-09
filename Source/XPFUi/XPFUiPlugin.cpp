#include "XPFUiPlugin.h"
#include "IXPFPluginHelper.h"
#include "XPFTopicDef.h"
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

    g_pPluginHelper->subMessage(this, TOPIC_Ui, XPFUi::HIDE_POPUP_ID);
    g_pPluginHelper->subMessage(this, TOPIC_Ui, XPFUi::SHOW_POPUP_ID);
}

QWidget* XPFUiPlugin::getWidget(const QString& WID) {
    QString path = QString("%0/XPFUi/%1.xml")
                       .arg(g_pPluginHelper->getXPFBinConfigDir())
                       .arg(WID);
    QWidget* widget = XPFUiTool::generateWidget(path);
    return widget;
}

QString XPFUiPlugin::getPluginName() {
    return QString("XPFUiPlugin");
}

void XPFUiPlugin::release() {
    g_pPluginHelper->unsubMessage(this, TOPIC_Ui, XPFUi::HIDE_POPUP_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_Ui, XPFUi::SHOW_POPUP_ID);
}

void XPFUiPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)
    if (topic == TOPIC_Ui) {
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
