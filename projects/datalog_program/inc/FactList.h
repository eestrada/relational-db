#if !defined(__FACTLIST_H__)
#define __FACTLIST_H__
#include <queue>
#include <string>
#include "Fact.h"

class FactList : public std::queue<Fact>
{
private:
public:
    FactList();
    ~FactList();

    std::string toString();
};

#endif //defined __FACTLIST_H__

