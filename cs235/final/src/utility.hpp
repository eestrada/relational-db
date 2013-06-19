#if !defined(_UTILITY_HPP_)
#define _UTILITY_HPP_

namespace ede
{
    
template < typename T >
struct less
{
    bool operator()(const T &a, const T &b)
    {
        return (a < b);
    }
};

}

#endif // Defined _UTILITY_HPP_

