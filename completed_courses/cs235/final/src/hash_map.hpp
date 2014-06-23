#if !defined(_HASH_MAP_HPP_)
#define _HASH_MAP_HPP_

//#include "deque.hpp"
//#include "list.hpp"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <list>
#include <utility>
#include "utility.hpp"

namespace ede
{

template <  typename Key,
            typename Val,
            typename Hash = hash<Key> >
class hash_map
{
public: // Member typedefs
    typedef Key key_type;
    typedef Val value_type;
    typedef pair< key_type, value_type > entry_type;
    typedef Hash hash_function_type;

public: // Public member types
    // Forward declarations
    class iterator;
    class const_iterator;

public: //Public member functions
    hash_map() : hash_fcn(), num_keys(0), the_buckets(INITIAL_CAPACITY),
        LOAD_THRESHOLD(3.0) {}

    void clear();
    void rehash();

    pair<iterator, bool> insert(const entry_type &entry)
    {
        // Is it time to rehash?
        double load_factor = double(num_keys) / the_buckets.size();
        if(load_factor > LOAD_THRESHOLD) rehash();

        // Find correct bucket
        size_t index = hash_fcn(entry.first) % the_buckets.size();

        // Find key in bucket
        listiter begin = the_buckets[index].begin();
        listiter end = the_buckets[index].end();

        listiter where = std::find_if(begin, end, key_check<Key, Val>(entry.first));

        // Return iterator based
        if(where != end) return pair<iterator, bool>(where, false);
        else throw std::runtime_error("Not implemented yet.");
    }

    pair<iterator, bool> insert(const key_type &k, const value_type &v)
        { return this->insert(entry_type(k, v)); }

    bool erase(const key_type &k);

    value_type & operator[](const key_type &k);
    const value_type & operator[](const key_type &k) const;

    value_type & at(const key_type &k);
    const value_type & at(const key_type &k) const;

protected: // Protected member typedefs
    typedef typename std::list<entry_type>::iterator listiter;
    
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

#include "hash_map.inl"

#endif // Defined _HASH_MAP_HPP_
