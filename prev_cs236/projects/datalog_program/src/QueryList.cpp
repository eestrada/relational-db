#include "QueryList.hpp"

std::string QueryList::toString() const
{
    return std::string();
}

std::ostream & operator<<(std::ostream &out, const QueryList &qlist)
{
    return out << qlist.toString();
}

