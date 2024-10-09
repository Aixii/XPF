#include "IRTestMainPagePlugin.h"
#include "IRTestMainDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFDB/IXPFDbServiceFactory.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRTestMainPagePlugin::IRTestMainPagePlugin()
    : m_TestMainWgt(nullptr) {
    qRegisterMetaType<uint32_t>("uint32_t");
}

IRTestMainPagePlugin::~IRTestMainPagePlugin() {
}

void IRTestMainPagePlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_TestMainWgt == nullptr) {
        m_TestMainWgt = new IR_TestOperatorWgt;
        m_TestMainWgt->init();
    }

    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();
    QObject::connect(handler, &IRTestMainDataHandler::sigConnectedNotify, m_TestMainWgt, &IR_TestOperatorWgt::slotDevConnected);
    QObject::connect(handler, &IRTestMainDataHandler::sigDisconnectedNotify, m_TestMainWgt, &IR_TestOperatorWgt::slotDevDisconnected);
}

void IRTestMainPagePlugin::initAfterPlugin() {
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_CONNECTED_NOTIFY_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_SET_ZERO_RESP_ID);
}

QWidget* IRTestMainPagePlugin::getWidget(const QString& WID) {
    if (WID == "IR_TestMainWgt") {
        return m_TestMainWgt;
    }
    return Q_NULLPTR;
}

QString IRTestMainPagePlugin::getPluginName() {

    return QString("IRTestMainPagePlugin");
}

void IRTestMainPagePlugin::release() {
    QObject::disconnect(m_TestMainWgt, 0, 0, 0);

    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_CONNECTED_NOTIFY_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_DISCONNECTED_NOTIFY_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_SET_ZERO_RESP_ID);
}

void IRTestMainPagePlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)

    IRTestMainDataHandler* manager = Singleton<IRTestMainDataHandler>::GetInstance();

    manager->slotOnMessage(topic, msgid, param);
}
