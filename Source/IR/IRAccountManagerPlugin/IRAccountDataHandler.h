#ifndef IRAccountDataHandler_H
#define IRAccountDataHandler_H

#include "Singleton.h"
#include <QObject>

class IRAccountDataHandler : public QObject {
    Q_OBJECT
    SINGLETON(IRAccountDataHandler)
public slots:
    void slotLoginFromWgt(const QString& username, const QString& password);

    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

signals:
    void sigLoginResult(bool ok, const QString& message);

private:
    void loginSucceed();

private:
    QString m_UserName;
};

#endif // IRAccountDataHandler_H
