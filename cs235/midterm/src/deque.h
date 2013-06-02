#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdexcept>

template < typename T >
class deque
{
public:
    deque();
    ~deque();

    const T & operator[](size_t index) const;
    T & operator[](size_t index);

    const T & at(size_t index) const;
    T & at(size_t index);

    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();
    T pop_front(bool);
    T pop_back(bool);

    const T & front() const;
    T & front();

    const T & back() const;
    T & back();

    void swap(deque<T> &other);
    bool empty() const;
    size_t size() const;
    void resize(size_t size);
    void clear();
private:
    void reallocate();

private:
    static const size_t DEFAULT_CAPACITY = 8;

    size_t capacity, num_items, front_index, rear_index;
    T *the_data;
};

#include "deque.inl"

#endif // Defined _DEQUE_H_
