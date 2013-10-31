#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

#include <stdexcept>

namespace ede
{

template < typename T >
class deque
{
public:
    #include "ra_iterator.hpp"
    typedef ra_iterator< T, deque<T> > iterator;
    typedef ra_iterator< T, const deque<T> > const_iterator;
public:
    deque();

    template < typename InputIterator >
    deque(InputIterator begin,
        InputIterator end);


    deque(const deque<T> &other);
    ~deque();

    T & operator[](size_t index) throw();
    const T & operator[](size_t index) const throw();

    T & at(size_t index) throw(std::out_of_range);
    const T & at(size_t index) const throw(std::out_of_range);

    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();

    T & front();
    const T & front() const;

    T & back();
    const T & back() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    void swap(deque<T> &other);
    bool empty() const;
    size_t size() const;

    void resize(size_t size);

    /*
     * Resets size, but not capacity.
     */
    void clear();

    /*
     * Resets capacity, but not size.
     */
    void shrink();

    bool operator==(const deque<T> &other);
    bool operator!=(const deque<T> &other);
    

private:
    void reallocate();

private:
    static const size_t DEFAULT_CAPACITY = 8;

    size_t capacity, num_items, front_index, rear_index;
    T *the_data;
};

#include "deque.inl"

} // End namespace ede

#endif // Defined _DEQUE_HPP_

