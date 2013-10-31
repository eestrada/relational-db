#include "RuleList.hpp"

std::string RuleList::toString() const
{
    return std::string();
}

std::ostream & operator<<(std::ostream &out, const RuleList &rlist)
{
    return out << rlist.toString();
}

