#include "deque.h"


template < typename T >
deque<T>::deque() : capacity(DEFAULT_CAPACITY), num_items(0), front_index(0),
    rear_index(0), the_data(new T[DEFAULT_CAPACITY]) {}

template < typename T >
deque<T>::~deque() { delete[] the_data; }

template < typename T >
void deque<T>::reallocate()
{
    size_t new_capacity = 2 * capacity;
    T *new_data = new T[new_capacity];
    size_t j = front_index;
    for(size_t i = 0; i < num_items; ++i)
    {
        new_data[i] = the_data[j];
        j = (j + 1) % capacity;
    }

    front_index = 0;
    rear_index = num_items - 1;
    capacity = new_capacity;

    T *tmp_ptr = the_data; the_data = new_data;

    delete[] tmp_ptr;
}

template < typename T >
void deque<T>::push_back(const T& data)
{
    if(num_items == capacity) this->reallocate();

    ++num_items;
    rear_index = (rear_index + 1) % capacity;
    the_data[rear_index] = item;
}

template < typename T >
void deque<T>::pop_front()
{
    front_index = (front_index + 1) % capacity;
    --num_items;
}

template < typename T >
void deque<T>::pop_back();

//template < typename T >
//T deque<T>::pop_front(int);

//template < typename T >
//T deque<T>::pop_back(int);

template < typename T >
const T & deque<T>::operator[](size_t index) const;

template < typename T >
T & deque<T>::operator[](size_t index);

template < typename T >
const T & deque<T>::at(size_t index) const;

template < typename T >
T & deque<T>::at(size_t index);

template < typename T >
const T & deque<T>::front() const
{
    return the_data[front_index];
}

template < typename T >
T & deque<T>::front()
{
    return the_data[front_index];
}

template < typename T >
const T & deque<T>::back() const
{
    return the_data[rear_index];
}

template < typename T >
T & deque<T>::back()
{
    return the_data[rear_index];
}

template < typename T >
void deque<T>::swap(Deque<T> &other)
{
    throw false;
}

template < typename T >
bool deque<T>::empty() const
{
    return this->num_items == 0;
}


template < typename T >
size_t deque<T>::size() const
{
    return num_items;
}

template < typename T >
void deque<T>::resize(size_t size)
{
    throw false;
}

