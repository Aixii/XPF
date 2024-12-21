#pragma once

#include <exception>

class IXPFErrorException : public std::exception {
public:
    IXPFErrorException() { }
    ~IXPFErrorException() { }
};
