#ifndef XPFCONFIGEXCEPTIONIMPL_H
#define XPFCONFIGEXCEPTIONIMPL_H

#include "IXPFConfigException"
#include <QString>

class XPFConfigExceptionImpl : public IXPFConfigException {
public:
    XPFConfigExceptionImpl(const QString& msg, int type);
    ~XPFConfigExceptionImpl();

    XPFConfigExceptionImpl& operator=(const XPFConfigExceptionImpl& other) {
        if (&other == this) {
            return *this;
        }

        memcpy(this->m_exp_msg, other.m_exp_msg, sizeof(m_exp_msg));
        m_exp_type = other.m_exp_type;

        return *this;
    }

    // exception interface
public:
    const char* what() const override;

    // IXPFConfigException interface
public:
    int exp_type() override;

private:
    char m_exp_msg[256];
    int  m_exp_type;
};

#endif // XPFCONFIGEXCEPTIONIMPL_H
