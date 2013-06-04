#ifndef _STACK_H_
#define _STACK_H_

#include "deque.h"

template < typename T, typename C = deque<T> >
class stack
{
public:
    stack() : container() {}
    ~stack() {} // Nothing allocated dynamically, so nothing to do.

    void push(const T &data)
    {
        this->container.push_back(data);
    }
    
    void pop()
    {
        this->container.pop_back();
    }

    T & top()
    {
        return this->container.back();
    }

    const T & top() const
    {
        return this->container.back();
    }

    size_t size() const
    {
        return this->container.size();
    }

    bool empty() const
    {
        return this->container.empty();
    }

    bool operator==(const stack<T> &other)
    {
        return this->container == other.container;
    }

    bool operator!=(const stack<T> &other)
    {
        return this->container != other.container;
    }

private:
    C container;
};

#endif // Defined _STACK_H_
