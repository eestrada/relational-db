#if !defined(__SCHEMELIST_H__)
#define __SCHEMELIST_H__
#include <queue>
#include <string>
#include "Scheme.h"

class SchemeList : public std::queue<Scheme>
{
private:
public:
    SchemeList();
    ~SchemeList();

    std::string toString();
};

#endif //defined __SCHEMELIST_H__
