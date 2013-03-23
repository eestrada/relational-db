#if !defined(__QUERYLIST_H__)
#define __QUERYLIST_H__

#include <vector>
#include <string>
#include <ostream>
#include "Query.hpp"

class QueryList : public std::vector<Query>
{
private:
public:
    QueryList();
    ~QueryList();

    std::string toString();
};

std::ostream & operator<<(std::ostream &out, const QueryList &qlist);

#endif //defined __QUERYLIST_H__

