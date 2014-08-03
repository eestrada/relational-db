#ifndef __ORDEREDSET_H__
#define __ORDEREDSET_H__

#include <set>
#include <vector>
#include <ostream>

namespace DB
{

using namespace std;

/*
 * Set that stores elements based on their insertion order.
 * The default internal representation is a std::vector, but
 * any sequence with a push_back function and begin, end, etc.
 * functions that returns forward iterators can be used. For
 * instance, std::deque and std::list.
 */
template < typename T, typename sequence=::std::vector<T> >
class OrderedSet : public sequence
{
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
        auto p = sorted.insert(val);
        if(p.second == true) sequence::push_back(val);
    }

    void clear()
    {
        sorted.clear();
        sequence::clear();
    }

    void join(const OrderedSet &other)
    {
        for(auto elem : other)
        {
            push_back(elem);
        }
    }

    OrderedSet operator+(const OrderedSet &other) const
    {
        OrderedSet retval = *this;

        retval.join(other);

        return retval;
    }

    OrderedSet & operator+=(const OrderedSet &other)
    {
        this->join(other);
        return *this;
    }

private:
        set<T> sorted;
};

} // end namespace DB

template < typename T >
std::ostream & operator<<(std::ostream &out, const DB::OrderedSet<T> &container)
{
    out << "[";
    for(auto i = container.cbegin(); i != container.cend(); ++i)
    {
        out << *i;

        auto icp = i;
        ++icp;
        if(icp != container.cend()) out << ", ";
    }
    out << "]";

    return out;
}


#endif // end include guard
