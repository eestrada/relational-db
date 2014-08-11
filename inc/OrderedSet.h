#ifndef __ORDEREDSET_H__
#define __ORDEREDSET_H__

//#include <map>
#include <unordered_map>
#include <list>
#include <ostream>

namespace DB
{

// using namespace std;

/*
 * Set that stores elements based on their insertion order.
 * The default internal representation is a std::list, but
 * any sequence with an insert function and begin, end, etc.
 * functions that returns forward iterators should be usable.
 * For instance, std::deque and std::vector. However, sequences
 * that are not linked lists may not behave properly when removing
 * values from the middle of the list as their iterators will become
 * invalid. In fact, on second thought, only use a linked list.
 */
template < typename T, typename sequence=::std::list<T>,
           typename dictionary=::std::unordered_map<T, typename sequence::iterator> >
class OrderedSet : public sequence
{
public:
    typedef sequence seq_type;
    typedef typename seq_type::iterator iterator;
    typedef typename seq_type::const_iterator const_iterator;
    typedef dictionary map_type;

public:
    OrderedSet() = default;
    OrderedSet(const OrderedSet &other) = default;
    OrderedSet(OrderedSet &&other) = default;

    template <typename C>
    OrderedSet(const C &other)
    {
        for(auto i : other)
        {
            push_back(i);
        }
    }

    OrderedSet & operator=(const OrderedSet &other) = default;
    OrderedSet & operator=(OrderedSet &&other) = default;

    void push_back(const T &val)
    {
        auto i = seq_type::insert(this->end(), val);
        auto p = sortedmap.insert({val, i});
        if(p.second == false) seq_type::pop_back();
    }

    void push_back(T &&rval)
    {
        T val = ::std::move(rval);
        auto i = seq_type::insert(this->end(), val);
        auto p = sortedmap.insert({val, i});
        if(p.second == false) seq_type::pop_back();
    }

    void clear()
    {
        sortedmap.clear();
        seq_type::clear();
    }

    void erase(const T &val)
    {
        auto iter = sortedmap.at(val);
        seq_type::erase(iter);
        sortedmap.erase(val);
    }

    template<typename C>
    void join(const C &other)
    {
        for(const auto &elem : other)
        {
            push_back(elem);
        }
    }

    template<typename C>
    OrderedSet operator+(const C &other) const
    {
        OrderedSet retval = *this;

        retval.join(other);

        return retval;
    }

    template<typename C>
    OrderedSet & operator+=(const C &other)
    {
        this->join(other);
        return *this;
    }

private:
        map_type sortedmap;
};

} // end namespace DB

template < typename T >
std::ostream & operator<<(std::ostream &out, const DB::OrderedSet<T> &container)
{
    out << "DB::OrderedSet(";
    out << "[";
    for(auto i = container.cbegin(); i != container.cend(); ++i)
    {
        out << *i;

        auto icp = i;
        ++icp;
        if(icp != container.cend()) out << ", ";
    }
    out << "]";
    out << ")";

    return out;
}


#endif // end include guard
