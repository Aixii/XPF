#include "DataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QStackedWidget>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

using namespace IRAccountManager;

DataHandler::DataHandler() {
}

DataHandler::~DataHandler() {
}

void IRAccountManager::DataHandler::slotLoginFromWgt(const QString& username, const QString& password) {
    IR::st_Login_Request request;
    snprintf(request.username, sizeof(request.username), "%s", username.toUtf8().data());
    snprintf(request.password, sizeof(request.password), "%s", password.toUtf8().data());

    QByteArray bytes;
    bytes.resize(sizeof(request));

    memcpy(bytes.data(), &request, sizeof(request));

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, IR::LOGIN_REQUEST_ID, bytes);
}

void DataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotOnMessage", Qt::QueuedConnection,
                                  Q_ARG(const QString&, topic),
                                  Q_ARG(uint32_t, msgid),
                                  Q_ARG(const QVariant&, param));
        return;
    }

    if (topic == TOPIC_IRAccount) {
        switch (msgid) {
        case IR::LOGIN_RESULT_ID: {
            QByteArray bytes = param.toByteArray();

            IR::st_Login_Result* result = reinterpret_cast<IR::st_Login_Result*>(bytes.data());
            if (result->result) {
                loginSucceed();
            }
        } break;
        default:
            break;
        }
    }
}

void DataHandler::loginSucceed() {
    QStackedWidget* widget = qobject_cast<QStackedWidget*>(g_pPluginHelper->getXPFWidgetById(0, "stackedwidget_main"));

    QWidget* mainwgt = g_pPluginHelper->getXPFWidgetById(0, "mainwgt");
    widget->setCurrentWidget(mainwgt);
}
