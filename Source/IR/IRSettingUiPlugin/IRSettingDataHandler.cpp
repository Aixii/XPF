#include "IRSettingDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QSettings>
#include <QStackedWidget>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

IRSettingDataHandler::IRSettingDataHandler()
    : dev_status(false) {
}

IRSettingDataHandler::~IRSettingDataHandler() {
}

void IRSettingDataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotOnMessage", Qt::QueuedConnection,
                                  Q_ARG(const QString&, topic),
                                  Q_ARG(uint32_t, msgid),
                                  Q_ARG(const QVariant&, param));
        return;
    }

    if (topic == TOPIC_IRAccount) {
        switch (msgid) {
        case IR::LOGIN_SUCCEED_ID: {
            QSettings settings("d.ini", QSettings::IniFormat);
            settings.beginGroup("TEST_PORT");
            QString port = settings.value("port", "").toString();
            settings.endGroup();

            if (!port.isEmpty()) {
                g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_SET_PORT_ID, port);
            }

        } break;
        default:
            break;
        }
    }
    else if (topic == TOPIC_IRTest) {
        switch (msgid) {
        case IR::DEV_CONNECTED_NOTIFY_ID:
            dev_status = true;
            break;
        case IR::DEV_DISCONNECTED_NOTIFY_ID:
            dev_status = false;
            break;
        default:
            break;
        }
    }
}
