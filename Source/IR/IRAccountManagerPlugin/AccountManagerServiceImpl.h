#ifndef ACCOUNTMANAGERSERVICEIMPL_H
#define ACCOUNTMANAGERSERVICEIMPL_H

#include "IAccountManagerService.h"
#include "IRTopicDef.h"
#include "Singleton.h"

class AccountManagerServiceImpl : public IAccountManagerService {
    SINGLETON(AccountManagerServiceImpl)

public:
    void setUserInfo(IR::st_UserInfo info);

    // IAccountManagerService interface
private:
    IR::st_UserInfo getCurrentUser() override;

private:
    IR::st_UserInfo m_userinfo;
};

#endif // ACCOUNTMANAGERSERVICEIMPL_H
