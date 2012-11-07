#ifndef _EDEIRQUEUE_HPP_
#define _EDEIRQUEUE_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class irdeque
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
    
    bool pop_left()
    {
        return sequence.pop_front();
    };
    
    bool pop_right()
    {
        return sequence.pop_back();
    };

    T & left()
    {
        return sequence.front();
    }

    T & right()
    {
        return sequence.back();
    }
};

};

#endif //_EDEIRQUEUE_HPP_


