#pragma once
#include <QDateTime>

class IXPFService {

public:
    IXPFService() {
    }
    ~IXPFService() {
    }

    static int getSequienceNumber();

private:
    static QDateTime m_CurTime;
    static int       count;
};

int IXPFService::getSequienceNumber() {
    QDateTime time = QDateTime::currentDateTime();
    int       code = time.toMSecsSinceEpoch() & 0xFFFFFF;
    code <<= 8;

    if (m_CurTime == time) {
        count++;
    }
    else {
        m_CurTime = time;

        count = 0;
    }
    code |= count;

    return code;
}
