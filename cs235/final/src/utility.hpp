#if !defined(_UTILITY_HPP_)
#define _UTILITY_HPP_

#include <string>

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

    /*
    template < typename S, typename T >
    bool operator==(const pair<S,T> &pr) const
    {return this->first == pr.first;}
    */
};


template < typename U, typename V >
struct key_check
{
    U key;

    key_check(const U &k) : key(k) {}

    bool operator()(const pair<U, V> &pr) const
    {
        return key == pr.first;
    }

private:
    key_check() : key() {}
    
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


/*
 * Generic hash for numeric types. Equivalent numeric types should evaluate equal.
 * (e.g. 0.0 = 0 = 0L = 0.0f)
 */
template < typename T >
struct hash
{
    size_t operator()(const T &var) const
    {
        return static_cast<size_t>(4262999287U * var);
    }
};

/*
 * Hash specialization for strings.
 */
template <>
struct hash<std::string>
{
    size_t operator()(const std::string &s) const
    {
        size_t result = 0;
        for(size_t i = 0; i < s.length(); ++i)
            result = result * 31 + s[i];
        return result;
    }
};

}

#endif // Defined _UTILITY_HPP_

