#ifndef USERDBMANAGER_H
#define USERDBMANAGER_H

#include <IXPFDbServiceFactory>
#include <QObject>

class UserDbManager : public QObject {
    Q_OBJECT
public:
    explicit UserDbManager(QObject* parent = nullptr);
    ~UserDbManager();

    void init();

public slots:
    void slotLogin(const QString& username, const QString& password);

private:
    std::shared_ptr<IXPFDbSyncService> m_DbService;
};

#endif // USERDBMANAGER_H
