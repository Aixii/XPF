#include "IRDevicePortManagerPlugin.h"
#include "IRDevicePortDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFDB/IXPFDbServiceFactory.h"
#include <QDebug>

IXPFPluginHelper* g_pPluginHelper = Q_NULLPTR;

IRDevicePortManagerPlugin::IRDevicePortManagerPlugin() {
    qRegisterMetaType<uint32_t>("uint32_t");
}

IRDevicePortManagerPlugin::~IRDevicePortManagerPlugin() {
}

void IRDevicePortManagerPlugin::initPlugin(IXPFPluginHelper* pluginHelper) {
    g_pPluginHelper = pluginHelper;

    IRDevicePortDataHandler* handler = Singleton<IRDevicePortDataHandler>::GetInstance();
}

void IRDevicePortManagerPlugin::initAfterPlugin() {

    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_SET_PORT_ID);
    g_pPluginHelper->subMessage(this, TOPIC_IRTest, IR::DEV_SET_ZERO_ID);
}

QWidget* IRDevicePortManagerPlugin::getWidget(const QString& WID) {
    Q_UNUSED(WID)
    return Q_NULLPTR;
}

QString IRDevicePortManagerPlugin::getPluginName() {

    return QString("IRDevicePortManagerPlugin");
}

void IRDevicePortManagerPlugin::release() {
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_SET_PORT_ID);
    g_pPluginHelper->unsubMessage(this, TOPIC_IRTest, IR::DEV_SET_ZERO_ID);

    Singleton<IRDevicePortDataHandler>::Destroy();
}

void IRDevicePortManagerPlugin::onMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    Q_UNUSED(sender)

    IRDevicePortDataHandler* manager = Singleton<IRDevicePortDataHandler>::GetInstance();

    manager->slotOnMessage(topic, msgid, param);
}
