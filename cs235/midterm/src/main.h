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
#include <typeinfo>

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

template < typename T >
inline void test_stack()
{
    stack<T> a;
    bool failed = false;

    std::clog << "\nTesting Stack ADT.\n";
    std::clog << "Of type: " << typeid(T).name() << "\n";

    std::clog << "Pushing 0 to 40 by 4s to top of stack.\n";

    for(int i = 0; i <=40; i+=4)
    {
        a.push(T(i));
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

template < typename T >
inline void test_queue()
{
    queue<T> a, b;
    bool failed = false;

    std::clog << "\nTesting Queue ADT.\n";
    std::clog << "Of type: " << typeid(T).name() << "\n";

    std::clog << "Pushing 0 to 40 by 4s to back of Queue A and Queue B.\n";

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

template < typename T >
inline void test_deque()
{
    deque<T> a,b;
    bool failed = false;

    std::clog << "\nTesting Deque ADT.\n";
    std::clog << "Of type: " << typeid(T).name() << "\n";

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

template < typename T >
inline void test_ir_deque()
{
    ir_deque<T> a, b;
    bool failed = false;

    std::clog << "\nTesting IR_Deque ADT.\n";
    std::clog << "Of type: " << typeid(T).name() << "\n";

    std::clog << "Pushing 0 to 40 by 4s to back of IR_Deque A and IR_Deque B.\n";
    for(int i = 0; i <=40; i+=4)
    {
        a.push(i);
        b.push(i);
    }

    std::clog << "Popping previously pushed values from front of IR_Deque A.\n";
    for(int i = 0; i <= 40; i+=4)
    {
        if(a.front() != i)
        {
            std::clog << "A Front returned: " << a.front() << ". Should have returned: ";
            std::clog << i << ".\n";
            std::clog << "Push/pop Queue test failed!\n\n";

            failed = true;
        }
        a.pop_front();
    }

    std::clog << "Popping previously pushed values from back of IR_Deque B.\n";
    for(int i = 40; i >= 0; i-=4)
    {
        if(b.back() != i)
        {
            std::clog << "B Back returned: " << b.back() << ". Should have returned: ";
            std::clog << i << ".\n";
            std::clog << "Push/pop Queue test failed!\n\n";

            failed = true;
        }
        b.pop_back();
    }
    // All other tests are extraneous since they are just wrapped around the
    // identical functions of the deque implementation. If deque passes, then
    // ir_deque would pass.

    if(failed)
        std::clog << "One or more IR_Deque tests failed!\n\n";
    else
        std::clog << "All IR_Deque tests passed!\n\n";

    std::clog << std::flush;
}

template < typename T >
inline void test_or_deque()
{
    or_deque<T> a, b;
    bool failed = false;

    std::clog << "\nTesting OR_Deque ADT.\n";
    std::clog << "Of type: " << typeid(T).name() << "\n";

    std::clog << "Pushing 0 to 40 by 4s to front of OR_Deque A and back of OR_Deque B.\n";

    for(int i = 0; i <=40; i+=4)
    {
        a.push_front(i);
        b.push_back(i);
    }

    std::clog << "Popping previously pushed values from front of OR_Deque A";
    std::clog << " and back of OR_Deque B.\n";

    for(int i = 40; i >= 0; i-=4)
    {
        // The values should count down from 40 to 0 in or_deque A.
        if(a.front() != i)
        {
            std::clog << "A Front returned: " << a.front() << ". Should have returned: ";
            std::clog << i << ".\n";
            std::clog << "Push/pop OR_Deque test failed!\n\n";

            failed = true;
        }

        // The back should always remain at the value of 40 until the last value is popped.
        if(b.back() != 40)
        {
            std::clog << "B Back returned: " << b.back() << ". Should have returned: ";
            std::clog << 40 << ".\n";
            std::clog << "Push/pop OR_Deque test failed!\n\n";

            failed = true;
        }
        a.pop();
        b.pop();
    }

    // All other tests are extraneous since they are just wrapped around the
    // identical functions of the deque implementation. If deque passes, then
    // queue would pass.

    if(failed)
        std::clog << "One or more OR_Deque tests failed!\n\n";
    else
        std::clog << "All OR_Deque tests passed!\n\n";

    std::clog << std::flush;
}

inline bool test_all()
{
    bool passed = true;

    // Tests all the ADTs with different data types to make sure it works as a template
    try
        { test_stack<short>(); test_stack<long>(); test_stack<double>(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_queue<short>(); test_queue<long>(); test_queue<double>(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_deque<short>(); test_deque<long>(); test_deque<double>(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_ir_deque<short>(); test_ir_deque<long>(); test_ir_deque<double>(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }
    try
        { test_or_deque<short>(); test_or_deque<long>(); test_or_deque<double>(); }
    catch(std::exception &e)
        { std::clog << "Exception encountered: " << e.what() << "\n"; passed=false; }

    if(passed == false)
        std::clog << "\nOne or more tests failed.\n\n";

    std::clog << std::flush;

    return passed;
}

#endif // Defined _MAIN_H_

