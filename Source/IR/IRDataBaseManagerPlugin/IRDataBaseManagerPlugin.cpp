#include "IRDataBaseManagerPlugin.h"
#include "IRTopicDef.h"
#include "IXPFDbServiceFactory"
#include "IXPFPluginHelper.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRDataBaseManagerPlugin::IRDataBaseManagerPlugin()
    : m_UserDbManager(nullptr) {
}

IRDataBaseManagerPlugin::~IRDataBaseManagerPlugin() {
}

void IRDataBaseManagerPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    m_SqlWaitThread = new QThread(this);
}

void IRDataBaseManagerPlugin::initAfterPlugin() {
    if (m_UserDbManager == nullptr) {
        m_UserDbManager = new UserDbManager();
        m_UserDbManager->init();

        m_UserDbManager->moveToThread(m_SqlWaitThread);
    }

    m_SqlWaitThread->start();

    g_pPluginHelper->subMessage(this, TOPIC_IRAccount, IR::LOGIN_REQUEST_ID);
}

QWidget* IRDataBaseManagerPlugin::getWidget(const QString& WID) {
    Q_UNUSED(WID);
    return Q_NULLPTR;
}

QString IRDataBaseManagerPlugin::getPluginName() {
    return QString("IRDataBaseManagerPlugin");
}

void IRDataBaseManagerPlugin::release() {
}

void IRDataBaseManagerPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)
    switch (msgid) {
    case IR::LOGIN_REQUEST_ID:
        if (topic == QString(TOPIC_IRAccount)) {
            QByteArray bytes = param.toByteArray();

            IR::st_Login_Request* result = reinterpret_cast<IR::st_Login_Request*>(bytes.data());
            m_UserDbManager->slotLogin(result->username, result->password);
        }
        break;
    default:
        break;
    }
}
