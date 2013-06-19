#ifndef _RA_ITERATOR_HPP_
#define _RA_ITERATOR_HPP_

/*
 * Class definition for generic random access iterators. only works with
 * sequence container ADTs with an "at" function taking an index as an input.
 */
template < typename E, typename Container >
class ra_iterator
{
public:
    typedef Container container_type;
    typedef E element_type;
public:
    ra_iterator() : index(-1), seq(NULL){}

    ra_iterator(const ra_iterator<E,Container> &other) : 
        index(other.index), seq(other.seq){}

    E & operator*() { return seq->at(index); }
    const E & operator*() const { return seq->at(index); }

    E * operator->() { return &(seq->at(index)); }
    const E * operator->() const { return &(seq->at(index)); }

    ra_iterator<E,Container> operator-(signed long i) const
    {
        ra_iterator<E,Container> tmp = *this;
        tmp.index -= i;
        return tmp;
    }

    ra_iterator<E,Container> operator+(signed long i) const
    {
        ra_iterator<E,Container> tmp = *this;
        tmp.index += i;
        return tmp;
    }

    ra_iterator<E,Container> & operator++()
    {
        this->index += 1;
        return *this;
    }

    /*
     * Postscript increment operator. Less efficient!
     */
    ra_iterator<E,Container> operator++(int)
    {
        ra_iterator<E,Container> tmp = *this; 
        this->index += 1;
        return tmp;
    }

    ra_iterator<E,Container> & operator--()
    {
        this->index -= 1;
        return *this;
    }

    /*
     * Postscript decrement operator. Less efficient!
     */
    ra_iterator<E,Container> operator--(int)
    {
        ra_iterator<E,Container> tmp = *this; 
        this->index -= 1;
        return tmp;
    }

private:
    ra_iterator(size_t i, Container *s) : index(i), seq(s){}
    size_t index;
    Container *seq;
};

#endif // Defined _RA_ITERATOR_HPP_
