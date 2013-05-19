#ifndef _EDEQUEUE_HPP_
#define _EDEQUEUE_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class queue
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

    T front()
    {
        return sequence.back();
    };

    T back()
    {
        return sequence.front();
    };

    bool push(T value)
    {
        sequence.push_front(value);
        return true;
    };

    bool pop()
    {
        if(sequence.empty())
            {return false;}
        
        sequence.pop_back();
        return true;
    };
};

};

#endif //_EDEQUEUE_HPP_

