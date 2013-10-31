#ifndef _EDELIST_HPP_
#define _EDELIST_HPP_

#include <list>
#include <stdexcept>

namespace ede
{

template <class T >
class list : public std::list<T>
{
public:

    // Constructors
    explicit list<T>(): std::list<T>(){};
    explicit list<T>(unsigned int n, const T& value = T()): std::list<T>(n, value){};

    template <class InputIterator>
        list(InputIterator first, InputIterator last): std::list<T>(first, last){};

    list<T>(const std::list<T> &other): std::list<T>(other){};
    
    /**
     * Index member function. Inefficient, but more convenient than iterators.
     * @param index Index within list to access.
     * @return A reference to the value at the index listed. As a reference it can both be read from and written to.
     */
    T& operator[](unsigned int index) throw(std::out_of_range)
    {
        typename ede::list<T>::iterator iter = this->begin();
        unsigned int i = 0;

        if(index >= 0 && index < this->size())
        {
            while(iter != this->end())
            {
                if(i == index)
                { break;}
                else
                {
                    ++i;
                    ++iter;
                }
            }
        }
        else
        {
            throw std::out_of_range("Unable to get non-existent list members.");
        }

        return *iter;
    };
    
    /**
     * At member function. Inefficient, but more convenient than iterators. This is simply a wrapper function around the operator[] member function.
     * @param index Index within list to access.
     * @return A reference to the value at the index listed. As a reference it can both be read from and written to.
     */
    T& at(unsigned int index) throw(std::out_of_range)
    {
        return this->operator[](index);
    };

    /**
     * Insert by index. As with the other containers of the STL, this inserts
     * BEFORE the indicated index. Less flexible than using iterators, but also
     * more convenient. Iterator style insertion is still available since it is
     * inherited from std::list.
     *
     * @param index The index before which to insert the value val.
     * @param val Value to insert before index.
     */
    void insert(unsigned int index, const T &val) throw(std::out_of_range)
    {
        typename ede::list<T>::iterator iter = this->begin();
        unsigned int i = 0;

        if(index >= 0 && index < this->size())
        {
            while(iter != this->end())
            {
                if(i == index)
                { break;}
                else
                {
                    ++i;
                    ++iter;
                }
            }
        }
        else
        {
            throw std::out_of_range("Unable to insert before non-existent index.");
        }

        // Insert with iterator. This is a function of the parent class.
        std::list<T>::insert(iter, val);

        return;
    };
};

};

#endif // define _EDELIST_HPP_

