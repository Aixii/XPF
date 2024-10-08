#include "DataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"

extern IXPFPluginHelper* g_pPluginHelper;

using namespace IRAccountManager;

DataHandler::DataHandler() {
}

DataHandler::~DataHandler() {
}

void IRAccountManager::DataHandler::slotLoginFromWgt(const QString& username, const QString& password) {
    IR::st_Login_Request request;
    snprintf(request.username, sizeof(request.username), "%s", username.toUtf8());
    snprintf(request.password, sizeof(request.password), "%s", password.toUtf8());

    QByteArray bytes;
    bytes.resize(sizeof(request));

    memcpy(bytes.data(), &request, sizeof(request));

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, IR::LOGIN_REQUEST_ID, bytes);
}
