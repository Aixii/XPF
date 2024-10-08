#include "IRAccountManagerPlugin.h"
#include "DataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFDB/IXPFDbServiceFactory.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRAccountManagerPlugin::IRAccountManagerPlugin()
    : m_LoginWgt(nullptr) {
}

IRAccountManagerPlugin::~IRAccountManagerPlugin() {
}

void IRAccountManagerPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    if (m_LoginWgt == nullptr) {
        m_LoginWgt = new IR_LoginWgt;
    }
}

void IRAccountManagerPlugin::initAfterPlugin() {
    IRAccountManager::DataHandler* manager = Singleton<IRAccountManager::DataHandler>::GetInstance();

    QObject::connect(m_LoginWgt, &IR_LoginWgt::sigLogin, manager, &IRAccountManager::DataHandler::slotLoginFromWgt);
}

QWidget* IRAccountManagerPlugin::getWidget(const QString& WID) {
    if (WID == "IR_LoginWgt") {
        return m_LoginWgt;
    }
    return Q_NULLPTR;
}

QString IRAccountManagerPlugin::getPluginName() {

    return QString("XPFLogin");
}

void IRAccountManagerPlugin::release() {
    QObject::disconnect(m_LoginWgt, 0, 0, 0);
}

void IRAccountManagerPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(msgid)
    Q_UNUSED(param)
    Q_UNUSED(sender)
}
