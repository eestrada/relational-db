#if !defined(_PQUEUE_HPP_)
#define _PQUEUE_HPP_

#include "deque.hpp"
#include "utility.hpp"

namespace ede
{

template <  typename T, typename Container = ::ede::deque<T>,
            typename Compare = ::ede::less<T> >
class pqueue
{
public:
    typedef T element_type;
    typedef Container container_type;
    typedef Compare comparison_functor;

    pqueue();
    ~pqueue() throw();

    void push(const T &data);

    const T& top() const;
    T& top();

    void pop();

    operator bool() const;
    bool empty() const;
    size_t size() const;

protected:
    Container seq;
    Compare comp_func;
};

}

#include "pqueue.inl"



#endif // Defined _PQUEUE_HPP_
