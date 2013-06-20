#if !defined(_PQUEUE_INL_)
#define _PQUEUE_INL_

namespace ede
{

template <  typename T, typename Container, typename Compare >
pqueue<T, Container, Compare>::pqueue() : seq(), comp_func()
{
    std::cerr << "pqueue<>::push function is not implemented properly yet." << std::endl;
    std::cerr << "pqueue<>::pop function is not implemented properly yet." << std::endl;
}

template <  typename T, typename Container, typename Compare >
pqueue<T, Container, Compare>::~pqueue() throw() {}

template <  typename T, typename Container, typename Compare >
void pqueue<T, Container, Compare>::push(const T &data)
{
    seq.push_back(data);
}

template <  typename T, typename Container, typename Compare >
const T& pqueue<T, Container, Compare>::top() const
{
    return seq.front();
}

template <  typename T, typename Container, typename Compare >
T& pqueue<T, Container, Compare>::top()
{
    return seq.front();
}

template <  typename T, typename Container, typename Compare >
void pqueue<T, Container, Compare>::pop()
{
    seq.pop_front();
}

template <  typename T, typename Container, typename Compare >
pqueue<T, Container, Compare>::operator bool() const
{
    return !(this->empty());
}

template <  typename T, typename Container, typename Compare >
bool pqueue<T, Container, Compare>::empty() const
{
    return this->size() == 0;
}

template <  typename T, typename Container, typename Compare >
size_t pqueue<T, Container, Compare>::size() const
{
    return seq.size();
}

}

#endif // Defined _PQUEUE_INL_
