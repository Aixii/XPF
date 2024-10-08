#include "IRAccountDataHandler.h"
#include "AccountManagerServiceImpl.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include <QStackedWidget>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

// using namespace IRAccountManager;

IRAccountDataHandler::IRAccountDataHandler() {
}

IRAccountDataHandler::~IRAccountDataHandler() {
}

void IRAccountDataHandler::slotLoginFromWgt(const QString& username, const QString& password) {
    IR::st_Login_Request request;
    snprintf(request.username, sizeof(request.username), "%s", username.toUtf8().data());
    snprintf(request.password, sizeof(request.password), "%s", password.toUtf8().data());

    QByteArray bytes;
    bytes.resize(sizeof(request));

    memcpy(bytes.data(), &request, sizeof(request));

    m_UserName = username;

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, IR::LOGIN_REQUEST_ID, bytes);
}

void IRAccountDataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
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

            emit sigLoginResult(result->result, result->message);
        } break;
        case IR::LOGIN_USER_INFO_ID: {
            QByteArray bytes = param.toByteArray();

            IR::st_UserInfo userinfo;
            if (0 == userinfo.unpack(bytes.data(), bytes.size())) {
                break;
            }

            AccountManagerServiceImpl* service = Singleton<AccountManagerServiceImpl>::GetInstance();
            service->setUserInfo(userinfo);

            g_pPluginHelper->sendMessage(TOPIC_IRAccount, IR::LOGIN_SUCCEED_ID);
        }
        default:
            break;
        }
    }
}

void IRAccountDataHandler::loginSucceed() {

    QStackedWidget* widget = qobject_cast<QStackedWidget*>(g_pPluginHelper->getXPFWidgetById(0, "stackedwidget_main"));

    QWidget* mainwgt = g_pPluginHelper->getXPFWidgetById(0, "mainwgt");
    widget->setCurrentWidget(mainwgt);
}
