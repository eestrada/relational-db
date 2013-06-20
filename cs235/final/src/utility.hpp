#if !defined(_UTILITY_HPP_)
#define _UTILITY_HPP_

namespace ede
{

template < typename U, typename V >
struct pair
{
    typedef U first_type;
    typedef V second_type;

    first_type first;
    second_type second;

    template < typename S, typename T >
    pair(const pair<S,T> &pr) : first(pr.first), second(pr.second) {}
    
    pair(): first(), second() {}
    pair(const first_type &f, const second_type &s): first(f), second(s) {}
    ~pair() {}
};

template < typename T >
struct less
{
    bool operator()(const T &a, const T &b) const
    {
        return (a < b);
    }
};

template < typename T >
struct greater
{
    bool operator()(const T &a, const T &b) const
    {
        return (a > b);
    }
};

}

#endif // Defined _UTILITY_HPP_

