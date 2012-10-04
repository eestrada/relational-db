#ifndef _EELIST_HPP_
#define _EELIST_HPP_

#include <list>
#include <iterator>


template <class T>
class eelist
{
private:
    class eelnode
    {
        T data;
        eelnode *prev, *next;
    };

    eelnode *head, *tail;
    unsigned long int nodecount;

public:

    class iterator : std::iterator<std::random_access_iterator_tag, T>
    {
        friend class eelist<T>;

        private:
            eelist<T> *parent;
            eelist<T>::eelnode *current;

        public:
            iterator()
            {
                parent = NULL;
                current = NULL;
            };
            ~iterator();

            T operator*()
            {
                return current->data;
            };

            iterator& operator++()
            {
                this = this->next;
                return *this;
            };

            iterator operator++(int)
            {
                iterator temp = *this;
                this->operator++();
                return temp;
            };

            iterator& operator--();
            iterator operator--(int);
            T operator[](unsigned long int index);
    };


public:

    T operator[](unsigned long int index)
    {
        return index;
    };
};

#endif // define _EELIST_HPP_
