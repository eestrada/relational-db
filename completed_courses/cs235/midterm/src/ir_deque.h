#ifndef _IR_DEQUE_H_
#define _IR_DEQUE_H_

#include "deque.h"

template < typename T, typename C = deque<T> >
class ir_deque
{
public:
    ir_deque() : container() {}
    ~ir_deque() {} // Nothing allocated dynamically, so nothing to do here.

    void push(const T &data)
    {
        this->container.push_back(data);
    }
    
    void pop_front()
    {
        this->container.pop_front();
    }

    void pop_back()
    {
        this->container.pop_back();
    }

    T & front()
    {
        return this->container.front();
    }

    const T & front() const
    {
        return this->container.front();
    }

    T & back()
    {
        return this->container.back();
    }

    const T & back() const
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

    bool operator==(const queue<T> &other)
    {
        return this->container == other.container;
    }

    bool operator!=(const queue<T> &other)
    {
        return this->container != other.container;
    }

private:
    C container;
};
#endif // Defined _IR_DEQUE_H_

