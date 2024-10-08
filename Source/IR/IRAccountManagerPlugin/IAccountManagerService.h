#ifndef IACCOUNTMANAGERSERVICE_H
#define IACCOUNTMANAGERSERVICE_H

#include "IRTopicDef.h"
#include "IXPFService.h"

static char IAccountManagerServiceIID[] = "IAccountManagerServiceIID";

class Q_DECL_EXPORT IAccountManagerService : public IXPFService {
public:
    IAccountManagerService() {
        Q_UNUSED(IAccountManagerServiceIID)
    }

    ~IAccountManagerService() { }

    virtual IR::st_UserInfo getCurrentUser() = 0;
};

#endif // IACCOUNTMANAGERSERVICE_H
