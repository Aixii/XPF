#include "UserDbManager.h"
#include "IRTopicDef.h"
#include "ISqlResult"
#include "IXPFPluginHelper.h"
#include <QDebug>
#include <QSqlError>
#include <QThread>

extern IXPFPluginHelper* g_pPluginHelper;

static char tb_name[] = "tb_user";

UserDbManager::UserDbManager(QObject* parent)
    : QObject(parent) {
}

UserDbManager::~UserDbManager() {
}

void UserDbManager::init() {
    IXPFDbServiceFactory* factory = dynamic_cast<IXPFDbServiceFactory*>(g_pPluginHelper->getService(IXPFDbServiceFactoryIID));

    QVariantMap attrs;
    attrs[XPFDB::ATTR_DBNAME] = "ir.db";

    m_DbService = factory->createXPFDbSyncService(XPFDB::QSQLITE3, "user", attrs);

    QString sql = QString("CREATE TABLE IF NOT EXISTS %0 ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "grade INTEGER,"
                          "status INTEGER,"
                          "username VARCHAR(16),"
                          "password VARCHAR(16),"
                          "usercode VARCHAR(16),"
                          "phone VARCHAR(11),"
                          "finger_index INTEGER,"
                          "finger_image BLOB)")
                      .arg(tb_name);

    SqlResult* result = nullptr;
    if (!m_DbService->exec(sql, &result)) {
        qDebug() << result->error().text();
    }

    delete result;
}

void UserDbManager::slotLogin(const QString& username, const QString& password) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotLogin", Qt::QueuedConnection, Q_ARG(const QString&, username), Q_ARG(const QString&, password));
        return;
    }

    using namespace IR;

    QString sql = QString("SELECT count(*) as count WHERE username=%0 AND password=%1").arg(username).arg(password);

    st_Login_Result result;

    SqlResult* sqlresult = nullptr;

    if (!m_DbService->exec(sql, &sqlresult)) {
        qDebug() << sqlresult->error().text();
        result.result = false;
        snprintf(result.message, sizeof(result.message), "%s", u8"内部错误");
    }
    else {
        if (sqlresult->rowData(0, 0).toInt() > 0) {
            result.result = true;
            snprintf(result.message, sizeof(result.message), "%s", u8"登录成功");
        }
        else {
            result.result = false;
            snprintf(result.message, sizeof(result.message), "%s", u8"账户或密码错误");
        }
    }

    delete sqlresult;

    QByteArray bytes;
    bytes.resize(sizeof(result));
    memcpy(bytes.data(), &result, sizeof(result));

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, LOGIN_RESULT_ID, bytes);
}
