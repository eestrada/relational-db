#if !defined(_PQUEUE_HPP_)
#define _PQUEUE_HPP_

#include <vector>
#include "deque.hpp"
#include "utility.hpp"

namespace ede
{

template <  typename T, typename Container = std::vector<T>,
            typename Compare = less<T> >
class priority_queue
{
public:
    typedef T element_type;
    typedef Container container_type;
    typedef Compare comparison_functor;

    priority_queue();
    ~priority_queue() throw();

    void push(const T &data);

    const T& top() const;
    T& top();

    void pop();

protected:
    Container seq;
    Compare comp_func;
};

}

#include "pqueue.inl"

#endif // Defined _PQUEUE_HPP_
