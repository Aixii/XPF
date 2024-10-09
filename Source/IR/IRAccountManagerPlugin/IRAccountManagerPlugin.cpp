#include "IRAccountManagerPlugin.h"
#include "AccountManagerServiceImpl.h"
#include "IRAccountDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFDB/IXPFDbServiceFactory.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRAccountManagerPlugin::IRAccountManagerPlugin()
    : m_LoginWgt(nullptr) {
    qRegisterMetaType<uint32_t>("uint32_t");
}

IRAccountManagerPlugin::~IRAccountManagerPlugin() {
}

void IRAccountManagerPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_LoginWgt == nullptr) {
        m_LoginWgt = new IR_LoginWgt;
        m_LoginWgt->init();
    }
}

void IRAccountManagerPlugin::initAfterPlugin() {
    IRAccountDataHandler* manager = Singleton<IRAccountDataHandler>::GetInstance();

    QObject::connect(m_LoginWgt, &IR_LoginWgt::sigLogin, manager, &IRAccountDataHandler::slotLoginFromWgt);
    QObject::connect(manager, &IRAccountDataHandler::sigLoginResult, m_LoginWgt, &IR_LoginWgt::slotLoginResult);

    g_pPluginHelper->subMessage(this, TOPIC_IRAccount, IR::LOGIN_RESULT_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRAccount, IR::LOGIN_USER_INFO_ID);

    IAccountManagerService* service = Singleton<AccountManagerServiceImpl>::GetInstance();
    g_pPluginHelper->registerService(IAccountManagerServiceIID, service);
}

QWidget* IRAccountManagerPlugin::getWidget(const QString& WID) {
    if (WID == "IR_LoginWgt") {
        return m_LoginWgt;
    }
    return Q_NULLPTR;
}

QString IRAccountManagerPlugin::getPluginName() {

    return QString("IRAccountManagerPlugin");
}

void IRAccountManagerPlugin::release() {
    QObject::disconnect(m_LoginWgt, 0, 0, 0);

    g_pPluginHelper->unsubMessage(this, TOPIC_IRAccount, IR::LOGIN_RESULT_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRAccount, IR::LOGIN_USER_INFO_ID);
}

void IRAccountManagerPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)

    IRAccountDataHandler* manager = Singleton<IRAccountDataHandler>::GetInstance();

    manager->slotOnMessage(topic, msgid, param);
}
