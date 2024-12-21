#pragma once

#include <exception>

class IXPFConfigException : public std::exception {
public:
    IXPFConfigException() { }
    virtual ~IXPFConfigException() { }
    virtual int exp_type() = 0;
};
