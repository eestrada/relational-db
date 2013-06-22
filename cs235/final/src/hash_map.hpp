#if !defined(_HASH_MAP_HPP_)
#define _HASH_MAP_HPP_

//#include "deque.hpp"
//#include "list.hpp"
#include <vector>
#include <list>
#include "utility.hpp"
#include <utility>

namespace ede
{

template <  typename Key,
            typename Val,
            typename Hash = ::ede::hash<Key> >
class hash_map
{
public: // Member typedefs
    typedef Key key_type;
    typedef Val value_type;
    typedef std::pair< key_type, value_type > entry_type;
    typedef Hash hash_function_type;

public: // Public member types
    class iterator;
    class const_iterator;

public: //Public member functions
    hash_map() : hash_fcn(), num_keys(0), the_buckets(INITIAL_CAPACITY), LOAD_THRESHOLD(3.0) {}
    void clear();

    std::pair<iterator, bool> insert(const entry_type &entry);
    std::pair<iterator, bool> insert(const key_type &k, const value_type &v);

    bool erase(const key_type &k);

    value_type & operator[](const key_type &k);
    const value_type & operator[](const key_type &k) const;

    value_type & at(const key_type &k);
    const value_type & at(const key_type &k) const;

protected: // Protected member functions
protected: // Protected member variables
    /* The hash function object. */
    hash_function_type hash_fcn;
    /* The number of keys (not hashes) in the map. */
    size_t num_keys;
    /* Buckets to hold linked lists with values. */
    std::vector< std::list<entry_type> > the_buckets;

    /* Useful constants. */
    const double LOAD_THRESHOLD;
    static const size_t INITIAL_CAPACITY = 100;
};

}

#endif // Defined _HASH_MAP_HPP_
