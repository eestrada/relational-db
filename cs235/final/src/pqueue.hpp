#if !defined(_PQUEUE_HPP_)
#define _PQUEUE_HPP_

#include <vector>
#include "deque.hpp"
#include "utility.hpp"

namespace ede
{

template <  typename T, typename Compare = ::ede::less<T>,
            typename Container = ::ede::deque<T> >
class pqueue
{
public: // public typedefs of template parameters
    typedef T element_type;
    typedef Container container_type;
    typedef Compare comparison_functor;

public: // public member function declarations
    pqueue();
    ~pqueue() throw();

    void push(const T &data);

    const T& top() const;

    void pop();

    operator bool() const;
    bool empty() const;
    size_t size() const;

protected: // protected member variables
    Container seq;
    Compare compare_func;
};

}

#include "pqueue.inl"



#endif // Defined _PQUEUE_HPP_
