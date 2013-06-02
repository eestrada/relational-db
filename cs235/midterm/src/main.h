#ifndef _MAIN_H_
#define _MAIN_H_

#include "deque.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class not_implemented : public std::exception
{
public:
    not_implemented(const std::string &s = "not implemented") :
        val(s) {}
    virtual ~not_implemented() throw() {}
    virtual const char* what() const throw() { return val.c_str(); }
private:
    std::string val;
};

inline void test_stack()
{
    throw not_implemented("stack test not implemented");
}

inline void test_queue()
{
    throw not_implemented("queue test not implemented");
}

inline void test_deque()
{
    deque<int> d;
    std::cerr << "Appending 0 to 500 by 5s to the back end.\n";

    for(size_t i = 0; i < 500; i+=5)
    {
        d.push_back(i);
    }

    for(size_t i = 0; i < d.size(); ++i)
    {
        std::cerr << "Index "<< i << ": " << d[i] << "\n";
    }
    std::clog << std::flush;
}

inline void test_ir_deque()
{
    throw not_implemented("ir_deque test not implemented");
}

inline void test_or_deque()
{
    throw not_implemented("or_deque test not implemented");
}

inline bool test_all()
{
    try
    {
        test_deque();
    }
    catch(std::exception &e)
    {
    }

    return bool();
}

#endif // Defined _MAIN_H_
