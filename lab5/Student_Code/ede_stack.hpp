#ifndef _EDESTACK_HPP_
#define _EDESTACK_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class stack
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

    T& top()
    {
        return sequence.back();
    };

    bool push(T value)
    {
        sequence.push_back(value);
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

#endif //_EDESTACK_HPP_

