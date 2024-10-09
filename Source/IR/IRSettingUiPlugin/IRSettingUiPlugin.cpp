#include "IRSettingUiPlugin.h"
#include "IRSettingDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRSettingUiPlugin::IRSettingUiPlugin()
    : m_SettingDialog(nullptr) {
    qRegisterMetaType<uint32_t>("uint32_t");
}

IRSettingUiPlugin::~IRSettingUiPlugin() {
}

void IRSettingUiPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_SettingDialog == nullptr) {
        m_SettingDialog = new IR_SettingDialog;
        m_SettingDialog->init();
    }
}

void IRSettingUiPlugin::initAfterPlugin() {
    IRSettingDataHandler* manager = Singleton<IRSettingDataHandler>::GetInstance();

    g_pPluginHelper->subMessage(this, TOPIC_IRAccount, IR::LOGIN_SUCCEED_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_CONNECTED_NOTIFY_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
}

QWidget* IRSettingUiPlugin::getWidget(const QString& WID) {
    if (WID == "IR_SettingDialog") {
        return m_SettingDialog;
    }
    return Q_NULLPTR;
}

QString IRSettingUiPlugin::getPluginName() {

    return QString("IRSettingUiPlugin");
}

void IRSettingUiPlugin::release() {
    QObject::disconnect(m_SettingDialog, 0, 0, 0);

    g_pPluginHelper->unsubMessage(this, TOPIC_IRAccount, IR::LOGIN_SUCCEED_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_CONNECTED_NOTIFY_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
}

void IRSettingUiPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)

    IRSettingDataHandler* manager = Singleton<IRSettingDataHandler>::GetInstance();

    manager->slotOnMessage(topic, msgid, param);
}
