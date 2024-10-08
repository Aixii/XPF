#include "IRMenuHeaderDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFDbServiceFactory"
#include "IXPFPluginHelper.h"
#include <QStackedWidget>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

IRMenuHeaderDataHandler::IRMenuHeaderDataHandler() {
}

IRMenuHeaderDataHandler::~IRMenuHeaderDataHandler() {
}

void IRMenuHeaderDataHandler::slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param) {
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
            emit sigLoginSucceed();
        } break;
        default:
            break;
        }
    }
}

void IRMenuHeaderDataHandler::slotLogoutFromWgt() {
    QStackedWidget* widget = qobject_cast<QStackedWidget*>(g_pPluginHelper->getXPFWidgetById(0, "stackedwidget_main"));

    QWidget* loginwgt = g_pPluginHelper->getXPFWidgetById(0, "loginwgt");
    widget->setCurrentWidget(loginwgt);

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, IR::LOGOUT_MSG_ID);
}
