#if !defined(_HASH_MAP_HPP_)
#define _HASH_MAP_HPP_

namespace ede
{

template < typename U, typename V >
struct pair
{
    typedef U first_type;
    typedef V second_type;

    first_type first;
    second_type second;

    pair(): first(), second() {}

    template < typename S, typename T >
    pair(const pair<S,T> &pr): first(pr.first), second(pr.second) {}
    
    pair(const first_type &f, const second_type &s): first(f), second(s) {}
    ~pair() {}

/*
    bool operator<(const kvpair<S, T> &other)
        {return (this->first < other.first);}

    bool operator>(const kvpair<S, T> &other)
        {return (this->first > other.first);}

    bool operator<=(const kvpair<S, T> &other)
        {return (this->first <= other.first);}

    bool operator>=(const kvpair<S, T> &other)
        {return (this->first >= other.first);}

    bool operator==(const kvpair<S, T> &other)
        {return (this->first == other.first);}

    bool operator!=(const kvpair<S, T> &other)
        {return (this->first != other.first);}
*/
};

template <  typename Key,
            typename Val,
            typename Compare = less<Key> >
class hash_map
{
public:
    typedef pair< Key, Val > Entry_type;
    typedef Key key_type;
    typedef Val value_type;
    typedef Compare key_compare;

public:

protected:
};

}

#endif // Defined _HASH_MAP_HPP_
