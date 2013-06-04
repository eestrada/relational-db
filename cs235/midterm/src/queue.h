#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "deque.h"

template < typename T, typename C = deque<T> >
class queue
{
public:
    void push(const T &data)
    {
        this->container.push_back(data);
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
#endif // Defined _QUEUE_H_

