#include "IRTestMainDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QThread>
#include <math.h>

extern IXPFPluginHelper* g_pPluginHelper;

IRTestMainDataHandler::IRTestMainDataHandler() {
}

IRTestMainDataHandler::~IRTestMainDataHandler() {
}

void IRTestMainDataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotOnMessage", Qt::QueuedConnection,
                                  Q_ARG(const QString&, topic),
                                  Q_ARG(uint32_t, msgid),
                                  Q_ARG(const QVariant&, param));
        return;
    }

    if (topic == TOPIC_IRTest) {
        switch (msgid) {
        case IR::DEV_CONNECTED_NOTIFY_ID: {
            emit sigConnectedNotify();
            dev_status = true;
        } break;
        case IR::DEV_DISCONNECTED_NOTIFY_ID: {
            emit sigDisconnectedNotify();
            dev_status = false;
        } break;
        case IR::DEV_SET_ZERO_RESP_ID: {
            QByteArray bytes = param.toByteArray();

            IR::st_Dev_Cmd_Resp* resp = reinterpret_cast<IR::st_Dev_Cmd_Resp*>(bytes.data());

            int index = log2(resp->irnum);

            if (resp->arg0 == 0x1) {
                QMessageBox::information(nullptr, u8"成功", QString(u8"杆 %0 设置零点成功").arg(index + 1), u8"确认");
            }
            else {
                QMessageBox::critical(nullptr, u8"失败", QString(u8"杆 %0 设置零点失败").arg(index + 1), u8"确认");
            }
        } break;
        default:
            break;
        }
    }
}
