#if !defined(__RULELIST_H__)
#define __RULELIST_H__
#include <queue>
#include <string>
#include "Rule.h"

class RuleList : public std::queue<Rule>
{
private:
public:
    RuleList();
    ~RuleList();

    std::string toString();
};

#endif //defined __RULELIST_H__

