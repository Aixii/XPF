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

    bool next_step = true;

    {
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
            next_step = false;
        }

        delete result;
    }

    if (!next_step) {
        return;
    }

    {
        QString sql = QString("SELECT COUNT(*) as count FROM %0 WHERE username='admin'").arg(tb_name);

        SqlResult* result = nullptr;
        if (!m_DbService->exec(sql, &result)) {
            qDebug() << result->error().text();
            next_step = false;
        }

        if (result->rowData(0, 0).toInt() > 0) {
            next_step = false;
        }

        delete result;
    }

    if (!next_step) {
        return;
    }

    {

        QString sql = QString("INSERT INTO %0 (id, grade, status, username, password, usercode, phone, finger_index, finger_image) "
                              "VALUES (1, 1, 0, 'admin', '88888888', '', '', 0, NULL)")
                          .arg(tb_name);

        SqlResult* result = nullptr;
        if (!m_DbService->exec(sql, &result)) {
            qDebug() << result->error().text();
        }

        delete result;
    }
}

void UserDbManager::slotLogin(const QString& username, const QString& password) {
    if (this->thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, "slotLogin", Qt::QueuedConnection, Q_ARG(const QString&, username), Q_ARG(const QString&, password));
        return;
    }

    using namespace IR;

    QStringList fields = { "id", "grade", "status", "username", "usercode", "phone", "finger_index", "finger_image" };

    QVariantMap condMap;
    condMap["username"] = username;
    condMap["password"] = password;

    st_Login_Result result;

    SqlResult* sqlresult = nullptr;

    if (!m_DbService->select(tb_name, fields, condMap, &sqlresult)) {
        qDebug() << sqlresult->error().text();
        result.result = false;
        snprintf(result.message, sizeof(result.message), "%s", u8"内部错误");
    }
    else {
        if (sqlresult->rowCount() > 0) {
            result.result = true;
            snprintf(result.message, sizeof(result.message), "%s", u8"登录成功");
        }
        else {
            result.result = false;
            snprintf(result.message, sizeof(result.message), "%s", u8"账户或密码错误");
        }
    }

    QByteArray bytes;
    bytes.resize(sizeof(result));
    memcpy(bytes.data(), &result, sizeof(result));

    g_pPluginHelper->sendMessage(TOPIC_IRAccount, LOGIN_RESULT_ID, bytes);

    if (result.result) {
        IR::st_UserInfo userinfo;
        userinfo.id     = sqlresult->rowData(0, 0).toInt();
        userinfo.grade  = sqlresult->rowData(0, 1).toInt();
        userinfo.status = sqlresult->rowData(0, 2).toInt();

        snprintf(userinfo.username, sizeof(userinfo.username), "%s", sqlresult->rowData(0, 3).toString().toUtf8().data());
        snprintf(userinfo.usercode, sizeof(userinfo.usercode), "%s", sqlresult->rowData(0, 4).toString().toUtf8().data());
        snprintf(userinfo.phone, sizeof(userinfo.phone), "%s", sqlresult->rowData(0, 5).toString().toUtf8().data());

        userinfo.finger_index = sqlresult->rowData(0, 6).toInt();
        userinfo.finger_image = sqlresult->rowData(0, 7).toByteArray();

        userinfo.image_size = userinfo.finger_image.size();

        QByteArray bytes;
        bytes.resize(userinfo.size());
        memset(bytes.data(), 0, bytes.size());
        userinfo.pack(bytes.data(), bytes.size());

        g_pPluginHelper->sendMessage(TOPIC_IRAccount, LOGIN_USER_INFO_ID, bytes);
    }

    delete sqlresult;
}
