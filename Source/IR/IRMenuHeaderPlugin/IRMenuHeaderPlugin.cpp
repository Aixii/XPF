#include "IRMenuHeaderPlugin.h"
#include "IRMenuHeaderDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFDB/IXPFDbServiceFactory.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRMenuHeaderPlugin::IRMenuHeaderPlugin()
    : m_MenuHeaderWgt(nullptr) {
}

IRMenuHeaderPlugin::~IRMenuHeaderPlugin() {
}

void IRMenuHeaderPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_MenuHeaderWgt == nullptr) {
        m_MenuHeaderWgt = new IR_MenuHeaderWgt;
        m_MenuHeaderWgt->init();
    }
}

void IRMenuHeaderPlugin::initAfterPlugin() {
    IRMenuHeaderDataHandler* handler = Singleton<IRMenuHeaderDataHandler>::GetInstance();

    QObject::connect(handler, &IRMenuHeaderDataHandler::sigLoginSucceed, m_MenuHeaderWgt, &IR_MenuHeaderWgt::slotLoginSuccessed);
    QObject::connect(m_MenuHeaderWgt, &IR_MenuHeaderWgt::sigLogout, handler, &IRMenuHeaderDataHandler::slotLogoutFromWgt);

    g_pPluginHelper->subMessage(this, TOPIC_IRAccount, IR::LOGIN_SUCCEED_ID);
}

QWidget* IRMenuHeaderPlugin::getWidget(const QString& WID) {
    if (WID == "IR_MenuHeaderWgt") {
        return m_MenuHeaderWgt;
    }
    return Q_NULLPTR;
}

QString IRMenuHeaderPlugin::getPluginName() {
    return QString("IRMenuHeaderPlugin");
}

void IRMenuHeaderPlugin::release() {
    QObject::disconnect(m_MenuHeaderWgt, 0, 0, 0);

    g_pPluginHelper->unsubMessage(this, TOPIC_IRAccount, IR::LOGIN_SUCCEED_ID);
}

void IRMenuHeaderPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)

    IRMenuHeaderDataHandler* manager = Singleton<IRMenuHeaderDataHandler>::GetInstance();

    manager->slotOnMessage(topic, msgid, param);
}
