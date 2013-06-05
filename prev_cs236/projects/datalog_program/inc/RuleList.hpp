#if !defined(__RULELIST_H__)
#define __RULELIST_H__

#include <vector>
#include <string>
#include <ostream>
#include "Rule.hpp"

class RuleList : public std::vector<Rule>
{
private:
public:
    RuleList(){}
    ~RuleList(){}

    std::string toString() const;
};

std::ostream & operator<<(std::ostream &out, const RuleList &rlist);

#endif //defined __RULELIST_H__
