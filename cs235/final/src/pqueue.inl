#if !defined(_PQUEUE_INL_)
#define _PQUEUE_INL_

namespace ede
{

template <  typename T, typename Compare, typename Container >
pqueue<T, Compare, Container>::pqueue() : seq(), compare_func() {}

template <  typename T, typename Compare, typename Container >
pqueue<T, Compare, Container>::~pqueue() throw() {}

template <  typename T, typename Compare, typename Container >
const T& pqueue<T, Compare, Container>::top() const
{
    return seq.front();
}

/*
template <  typename T, typename Compare, typename Container >
T& pqueue<T, Compare, Container>::top()
{
    return seq.front();
}
*/

template <  typename T, typename Compare, typename Container >
void pqueue<T, Compare, Container>::push(const T &data)
{
    seq.push_back(data);
    int child = this->size() - 1;
    int parent = (child - 1) / 2;

    while(parent >= 0 and compare_func(seq.at(child), seq.at(parent)))
    {
        T tmp = seq.at(parent);
        seq.at(parent) = seq.at(child);
        seq.at(child) = tmp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

template <  typename T, typename Compare, typename Container >
void pqueue<T, Compare, Container>::pop()
{
    seq.front() = seq.back();
    seq.pop_back();

    int parent = 0;

    while(true)
    {
        int lchild = (2 * parent) + 1, rchild = lchild + 1;

        if(lchild >= seq.size()) break;

        int min_child = lchild;
        if(rchild < seq.size() and compare_func(seq.at(rchild), seq.at(lchild)))
            { min_child = rchild; }

        if(compare_func(seq.at(min_child), seq.at(parent)))
        {
            T tmp = seq.at(parent);
            seq.at(parent) = seq.at(min_child);
            seq.at(min_child) = tmp;

            parent = min_child;
        }
        else break;
    }
}

template <  typename T, typename Compare, typename Container >
pqueue<T, Compare, Container>::operator bool() const
{
    return !(this->empty());
}

template <  typename T, typename Compare, typename Container >
bool pqueue<T, Compare, Container>::empty() const
{
    return this->size() == 0;
}

template <  typename T, typename Compare, typename Container >
size_t pqueue<T, Compare, Container>::size() const
{
    return seq.size();
}

}

#endif // Defined _PQUEUE_INL_
