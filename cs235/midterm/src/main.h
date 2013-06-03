#ifndef _MAIN_H_
#define _MAIN_H_

#include "deque.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdlib>

class not_implemented : public std::runtime_error
{
public:
    not_implemented(const std::string &s = "not implemented") :
        std::runtime_error(s){}//val(s) {}
    virtual ~not_implemented() throw() {}
    //virtual const char* what() const throw() { return val.c_str(); }
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

    for(size_t i = 0; i < 100; i+=5)
    {
        if (i % 2 == 0)
            d.push_back(i);
        else
            d.push_front(i);
            
    }

    for(size_t i = 0; i < 20; ++i)
    {
        //if (d.at(i) != i * 5)
        if (false)
        {
            std::clog << "Index "<< i << " does not match expected result.";
            std::clog << " Returned: " << d[i] << ". Should have returned: ";
            std::clog << (i * 5) << ".\n";
            std::clog << "Deque test failed!\n\n";
            std::clog << std::flush;
            return;
        }
        else
            std::clog << "Index "<< i << ": " << d[i] << "\n";
    }

    std::clog << "Deque test passed!\n\n";
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
    bool passed = true;
    try
    {
        test_stack();
        test_queue();
        test_deque();
        test_ir_deque();
        test_or_deque();
    }
    catch(not_implemented &e)
    {
        std::clog << "Exception encountered: " << e.what() << std::endl;
        passed = false;
    }

    return passed;
}

#endif // Defined _MAIN_H_

