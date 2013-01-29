#if !defined(__QUERYLIST_H__)
#define __QUERYLIST_H__
#include <queue>
#include <string>
#include "Query.h"

class QueryList : public std::queue<Query>
{
private:
public:
    QueryList();
    ~QueryList();

    std::string toString();
};

#endif //defined __QUERYLIST_H__

