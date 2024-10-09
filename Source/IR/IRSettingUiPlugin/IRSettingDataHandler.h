#ifndef IRSETTINGDATAHANDLER_H
#define IRSETTINGDATAHANDLER_H

#include "Singleton.h"
#include <QObject>

class IRSettingDataHandler : public QObject {
    Q_OBJECT
    SINGLETON(IRSettingDataHandler)
public slots:
    void slotOnMessage(const QString& topic, uint32_t msgid, const QVariant& param);

public:
    bool dev_status;
};

#endif // IRSETTINGDATAHANDLER_H
