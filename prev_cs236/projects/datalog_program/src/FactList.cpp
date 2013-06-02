#include "FactList.hpp"

std::string FactList::toString() const
{
    return std::string();
}

std::ostream & operator<<(std::ostream &out, const FactList &flist)
{
    return out << flist.toString();
}

