#if !defined(_HASH_MAP_HPP_)
#define _HASH_MAP_HPP_

#include "utility.hpp"

namespace ede
{

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
