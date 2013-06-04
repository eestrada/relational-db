#ifndef _MAIN_H_
#define _MAIN_H_

#include "deque.h"
#include "stack.h"
#include "queue.h"
#include "ir_deque.h"
#include "or_deque.h"
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
    stack<int> a;
    bool failed = false;

    std::clog << "\nTesting Stack ADT.\n";

    std::clog << "Pushing 0 to 40 by 4s to top of stack.\n";

    for(int i = 0; i <=40; i+=4)
    {
        a.push(i);
    }

    std::clog << "Popping previously pushed values from top of stack.\n";

    for(int i = 40; i >= 0; i-=4)
    {
        if(a.top() != i)
        {
            std::clog << "Top returned: " << a.top() << ". Should have returned: ";
            std::clog << i << ".\n";
            std::clog << "Push/pop Stack test failed!\n\n";

            failed = true;
        }
        a.pop();
    }

    // All other tests are extraneous since they are just wrapped around the
    // identical functions of the deque implementation. If deque passes, then
    // stack would pass.

    if(failed)
        std::clog << "One or more Stack tests failed!\n\n";
    else
        std::clog << "All Stack tests passed!\n\n";

    std::clog << std::flush;
}

inline void test_queue()
{
    queue<int> a, b;
    bool failed = false;

    std::clog << "\nTesting Queue ADT.\n";

    std::clog << "Pushing 0 to 40 by 4s to back of queue B and queue B.\n";

    for(int i = 0; i <=40; i+=4)
    {
        a.push(i);
        b.push(i);
    }

    std::clog << "Popping previously pushed values from front of queue.\n";

    for(int i = 0; i <= 40; i+=4)
    {
        if(a.front() != i)
        {
            std::clog << "A Front returned: " << a.front() << ". Should have returned: ";
            std::clog << i << ".\n";
            std::clog << "Push/pop Queue test failed!\n\n";

            failed = true;
        }

        if(b.back() != 40)
        {
            std::clog << "B Back returned: " << b.back() << ". Should have returned: ";
            std::clog << 40 << ".\n";
            std::clog << "Push/pop Queue test failed!\n\n";

            failed = true;
        }
        a.pop();
        b.pop();
    }

    // All other tests are extraneous since they are just wrapped around the
    // identical functions of the deque implementation. If deque passes, then
    // queue would pass.

    if(failed)
        std::clog << "One or more Queue tests failed!\n\n";
    else
        std::clog << "All Queue tests passed!\n\n";

    std::clog << std::flush;
}

inline void test_deque()
{
    deque<int> a,b;
    bool failed = false;

    std::clog << "\nTesting Deque ADT.\n";

    std::clog << "Appending 0 to 500 by 5s to the back end.\n";

    for(size_t i = 0; i < 500; i+=5)
    {
        a.push_back(i);
    }

    for(size_t i = 0; i < 100; ++i)
    {
        if (a.at(i) != int(i) * 5)
        {
            std::clog << "Index '"<< i << "' does not match expected result.";
            std::clog << " Returned: " << a[i] << ". Should have returned: ";
            std::clog << (i * 5) << ".\n";
            std::clog << "Deque push back test failed!\n\n";

            failed = true;
        }
    }

    std::clog << "Alternatively pushing 0 to 100 by 5s to the front and back ends.\n";

    for(size_t i = 0; i < 100; i+=5)
    {
        if (i % 2 == 0) // When even, push to back.
            b.push_back(i);
        else // When odd, push to front.
            b.push_front(i);
    }

    int result[] = {95,85,75,65,55,45,35,25,15,5,0,10,20,30,40,50,60,70,80,90};

    for(size_t i = 0; i < 20; ++i)
    {
        if (b.at(i) != result[i])
        {
            std::clog << "Index '"<< i << "' does not match expected result.";
            std::clog << " Returned: " << b[i] << ". Should have returned: ";
            std::clog << (i * 5) << ".\n";
            std::clog << "Deque push front and back test failed!\n\n";

            failed = true;
        }
    }

    std::clog << "Testing equality operators.\n";

    if(a == b)
    {
        failed = true;
        std::clog << "Failed equality testing.\n";
    }
    if(a != a)
    {
        failed = true;
        std::clog << "Failed inequality testing.\n";
    }

    if(failed)
        std::clog << "One or more Deque tests failed!\n\n";
    else
        std::clog << "All Deque tests passed!\n\n";

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
        { test_stack(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_queue(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_deque(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_ir_deque(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_or_deque(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }

    if(passed == false)
        std::clog << "\nOne or more tests failed.\n\n";

    std::clog << std::flush;

    return passed;
}

#endif // Defined _MAIN_H_

