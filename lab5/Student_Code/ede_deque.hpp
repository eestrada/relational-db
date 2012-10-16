#ifndef _EDE_DEQUE_HPP_
#define _EDE_DEQUE_HPP_

#include "ede_list.hpp"

namespace ede
{

template< class T, class C = ede::list<T> >
class deque : public C
{
};

};

#endif //_EDE_DEQUE_HPP_

