#ifndef XPFCONFIGEXCEPTIONIMPL_H
#define XPFCONFIGEXCEPTIONIMPL_H

#include "IXPFConfigException"
#include <QString>

class XPFConfigExceptionImpl : public IXPFConfigException {
public:
    XPFConfigExceptionImpl(const QString& msg, int type);
    ~XPFConfigExceptionImpl();

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
