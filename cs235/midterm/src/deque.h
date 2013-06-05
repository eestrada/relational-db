#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdexcept>

template < typename T >
class deque
{
public:
    deque();
    ~deque();

    /*
     * Subscript operator. It is theoretically possible to index beyond or below
     * the capacity of the deque without generating a segmentation fault. However,
     * this will very likely just return junk data.
     *
     * Use the "at" function to get bounds checking.
     */
    const T & operator[](size_t index) const;
    T & operator[](size_t index);

    const T & at(size_t index) const;
    T & at(size_t index);

    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();

    const T & front() const;
    T & front();

    const T & back() const;
    T & back();

    void swap(deque<T> &other);
    bool empty() const;
    size_t size() const;

    void resize(size_t size);

    /*
     * Resets size, but not capacity.
     */
    void clear();

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

#endif // Defined _DEQUE_H_

