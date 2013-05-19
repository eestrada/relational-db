#if !defined(__FACTLIST_H__)
#define __FACTLIST_H__

#include <vector>
#include <string>
#include <ostream>
#include "Fact.hpp"

class FactList : public std::vector<Fact>
{
private:
public:
    FactList(){}
    ~FactList(){}

    std::string toString() const;
};

std::ostream & operator<<(std::ostream &out, const FactList &flist);

#endif //defined __FACTLIST_H__

