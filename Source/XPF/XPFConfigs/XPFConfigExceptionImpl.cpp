#include "XPFConfigExceptionImpl.h"

XPFConfigExceptionImpl::XPFConfigExceptionImpl(const QString& msg, int type) {

    m_exp_type = type;

    memset(m_exp_msg, 0, sizeof(m_exp_msg));
    snprintf(m_exp_msg, sizeof(m_exp_msg), "%s", msg.toStdString().c_str());
}

XPFConfigExceptionImpl::~XPFConfigExceptionImpl() {
}

const char* XPFConfigExceptionImpl::what() const {
    return m_exp_msg;
}

int XPFConfigExceptionImpl::exp_type() {
    return m_exp_type;
}
