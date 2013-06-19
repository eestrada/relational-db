
template < typename T >
deque<T>::deque() :
    capacity(DEFAULT_CAPACITY),
    num_items(0),
    front_index(0),
    rear_index(DEFAULT_CAPACITY - 1),
    the_data(new T[DEFAULT_CAPACITY]) {}

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
void deque<T>::push_front(const T& data)
{
    if(num_items == capacity) this->reallocate();

    ++num_items;
    front_index = (front_index - 1) % capacity;
    the_data[front_index] = data;
}

template < typename T >
void deque<T>::push_back(const T& data)
{
    if(num_items == capacity) this->reallocate();

    ++num_items;
    rear_index = (rear_index + 1) % capacity;
    the_data[rear_index] = data;
}

template < typename T >
void deque<T>::pop_front()
{
    front_index = (front_index + 1) % capacity;
    --num_items;
}

template < typename T >
void deque<T>::pop_back()
{
    rear_index = (rear_index - 1) % capacity;
    --num_items;
}

/*
 * Subscript operator. Retrieve a reference to the variable at the given
 * index. It is possible to index beyond or below the capacity
 * of the deque without generating a segmentation fault. However, what is
 * returned is undefined and unknown.
 *
 * Instead, use the "at" function to get bounds checking.
 *
 * @param index
 *      Index at which to retrieve reference.
 */
template < typename T >
const T & deque<T>::operator[](size_t index) const throw()
{
    return the_data[(front_index + index) % capacity];
}

template < typename T >
T & deque<T>::operator[](size_t index) throw()
{
    return the_data[(front_index + index) % capacity];
}

/*
 * Retrieve a reference to the variable at the given index. This does
 * bounds checking, whereas the plain subscript operator does not.
 *
 * Throws a std::out_of_range exception when index is out of bounds.
 *
 * @param index
 *      Index at which to retrieve reference.
 */
template < typename T >
const T & deque<T>::at(size_t index) const throw(std::out_of_range)
{
    if(index < this->size())
        return (*this)[index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
T & deque<T>::at(size_t index) throw(std::out_of_range)
{
    if(index < this->size())
        return (*this)[index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
const T & deque<T>::front() const
{
    if(this->size() > 0)
        return the_data[front_index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
T & deque<T>::front()
{
    if(this->size() > 0)
        return the_data[front_index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
const T & deque<T>::back() const
{
    if(this->size() > 0)
        return the_data[rear_index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
T & deque<T>::back()
{
    if(this->size() > 0)
        return the_data[rear_index];
    else
        throw std::out_of_range("deque::out_of_range");
}

template < typename T >
bool deque<T>::operator==(const deque<T> &other)
{
    if(this->size() != other.size()) // If sizes don't match we aren't equal
        return false;
    else // compare individual members for equality
    {
        for(size_t i = 0; i < this->size(); ++i)
        {
            if((*this)[i] != other[i])
                return false;
        }
    }

    // If we made it down here then the deques must be equal
    return true;
}

template < typename T >
bool deque<T>::operator!=(const deque<T> &other)
{
    // Simply invert the equality operator
    return !((*this) == other);
}

template < typename T >
void deque<T>::swap(deque<T> &other)
{
    throw false;
}

template < typename T >
bool deque<T>::empty() const
{
    return this->size() == 0;
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

/*
 * Resets size, but not capacity.
 */
template < typename T >
void deque<T>::clear()
{
    num_items = 0;
    front_index = 0;
    rear_index = capacity - 1;
}

/*
 * Resets size, but not capacity.
 */
template < typename T >
typename deque<T>::iterator deque<T>::begin()
{
    return deque<T>::iterator(0, this);
}

template < typename T >
typename deque<T>::const_iterator deque<T>::begin() const
{
    return deque<T>::const_iterator(0, this);
}

template < typename T >
typename deque<T>::const_iterator deque<T>::cbegin() const
{
    return deque<T>::const_iterator(0, this);
}

template < typename T >
typename deque<T>::iterator deque<T>::end()
{
    return deque<T>::iterator(this->size(), this);
}

template < typename T >
typename deque<T>::const_iterator deque<T>::end() const
{
    return deque<T>::const_iterator(this->size(), this);
}

template < typename T >
typename deque<T>::const_iterator deque<T>::cend() const
{
    return deque<T>::const_iterator(this->size(), this);
}

