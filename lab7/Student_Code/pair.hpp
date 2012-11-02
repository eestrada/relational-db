#ifndef _PAIR_HPP_
#define _PAIR_HPP_

namespace ede
{

// This code is more or less what is found on:
// www.cplusplus.com/reference/std/utility/pair/
template < typename T1, typename T2 >
struct pair
{

    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}

    pair(const T1 &x, const T2 &y) : first(x), second(y) {}

    template < typename U, typename V >
        pair (const pair< U, V > &p) : first(p.first), second(p.second) {}
};

template < typename T1, typename T2 >
bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
    return (a.first == b.first);
}

template < typename T1, typename T2 >
bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
    return !(a.first == b.first);
}

template < typename T1, typename T2 >
bool operator>(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
    return a.first > b.first;
}

template < typename T1, typename T2 >
bool operator<(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
    return a.first < b.first;
}

};

template < typename T1 , typename T2>
ostream & operator<<(ostream &stream, const ede::pair<T1, T2> &somepair)
{
    string delim = " ";

    stream << somepair.first << delim << somepair.second;

    return stream;
}

#endif // define _PAIR_HPP_

