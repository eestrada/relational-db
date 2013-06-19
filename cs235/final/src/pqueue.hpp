#if !defined(_PQUEUE_HPP_)
#define _PQUEUE_HPP_

#include <vector>

namespace ede
{

template < typename T >
struct less
{
    bool operator()(const T &a, const T &b)
    {
        return (a < b);
    }
};

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
