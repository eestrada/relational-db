#if !defined(__SCHEMELIST_H__)
#define __SCHEMELIST_H__

#include <vector>
#include <string>
#include <ostream>
#include "Scheme.hpp"

class SchemeList : public std::vector<Scheme>
{
private:
public:
    SchemeList(){}
    ~SchemeList(){}

    std::string toString() const;
};

std::ostream & operator<<(std::ostream &out, const SchemeList &slist);

#endif //defined __SCHEMELIST_H__

