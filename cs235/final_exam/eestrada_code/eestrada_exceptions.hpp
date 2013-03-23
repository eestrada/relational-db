#pragma once

#include <string>
#include <exception>

namespace ede
{

class unimplemented : public std::exception
{
private:
    std::string whatstr;

public:
    unimplemented(const std::string &str) throw()
        : whatstr("Feature is not implemented: " + str) {}

    virtual ~unimplemented() throw(){}

    virtual const char* what() const throw()
    {
        return whatstr.c_str();
    }
};

}

