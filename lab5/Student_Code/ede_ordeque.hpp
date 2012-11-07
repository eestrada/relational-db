#ifndef _EDEORQUEUE_HPP_
#define _EDEORQUEUE_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class ordeque
{
private:
    C sequence;

public:

    bool empty()
    {
        return sequence.empty();
    };

    int size()
    {
        return sequence.size();
    };

    void push_left(T newval)
    {
        sequence.push_front(newval);
    };

    void push_right(T newval)
    {
        sequence.push_back(newval);
    };
    
    bool pop_left()
    {
        return sequence.pop_front();
    };

    T & left()
    {
        return sequence.front();
    }
};

};

#endif //_EDEORQUEUE_HPP_

