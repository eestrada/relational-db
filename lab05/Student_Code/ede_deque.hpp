#ifndef _EDE_DEQUE_HPP_
#define _EDE_DEQUE_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class deque : public C
{
public:

    void push_left(T newval)
    {
        this->push_front(newval);
    };

    void push_right(T newval)
    {
        this->push_back(newval);
    };
    
    bool pop_left()
    {
        return this->pop_front();
    };
    
    bool pop_right()
    {
        return this->pop_back();
    };

    T & left()
    {
        return this->front();
    }

    T & right()
    {
        return this->back();
    }
};

};

#endif //_EDE_DEQUE_HPP_

