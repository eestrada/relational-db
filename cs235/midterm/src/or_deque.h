#ifndef _OR_DEQUE_H_
#define _OR_DEQUE_H_

#include "deque.h"

template < typename T, typename C = deque<T> >
class or_deque
{
public:
    or_deque() : container() {}
    ~or_deque() {} // Nothing allocated dynamically, so nothing to do here.

    void push_back(const T &data)
    {
        this->container.push_back(data);
    }
    
    void push_front(const T &data)
    {
        this->container.push_front(data);
    }
    
    void pop()
    {
        this->container.pop_front();
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

