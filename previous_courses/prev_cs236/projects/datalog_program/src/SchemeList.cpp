#include "SchemeList.hpp"

std::string SchemeList::toString() const
{
    return std::string();
}

std::ostream & operator<<(std::ostream &out, const SchemeList &slist)
{
    return out << slist.toString();
}

