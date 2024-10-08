#include "AccountManagerServiceImpl.h"

AccountManagerServiceImpl::AccountManagerServiceImpl() {
}

AccountManagerServiceImpl::~AccountManagerServiceImpl() {
}

void AccountManagerServiceImpl::setUserInfo(IR::st_UserInfo info) {
    m_userinfo = info;
}

IR::st_UserInfo AccountManagerServiceImpl::getCurrentUser() {
    return m_userinfo;
}
