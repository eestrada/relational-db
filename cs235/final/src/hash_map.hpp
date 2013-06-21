#if !defined(_HASH_MAP_HPP_)
#define _HASH_MAP_HPP_

#include "deque.hpp"
//#include "list.hpp"
#include <vector>
#include <list>
#include "utility.hpp"

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
    typedef pair< key_type, value_type > entry_type;
    typedef Hash hash_function_type;

public: // Public member types
    class iterator;
    class const_iterator;

public: //Public member functions
    hash_map();
    ~hash_map();

    bool erase(const key_type &k);

    pair<iterator, bool> insert(const entry_type &entry);
    pair<iterator, bool> insert(const key_type &k, const value_type &v);
protected: // Protected member functions
protected: // Protected member variables
    /* The hash function object. */
    hash_function_type hash_fcn;
    size_t num_keys;
    ede::deque< std::list<entry_type> > the_buckets;
    static size_t INITIAL_CAPACITY;
    static const double LOAD_THRESHOLD;
    
};

}

#endif // Defined _HASH_MAP_HPP_
