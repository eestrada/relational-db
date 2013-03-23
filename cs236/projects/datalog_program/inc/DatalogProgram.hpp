#if !defined(__DATALOGPROGRAM_H__)
#define __DATALOGPROGRAM_H__

#include "SchemeList.hpp"
#include "QueryList.hpp"
#include "FactList.hpp"
#include "RuleList.hpp"
#include <ostream>

class DatalogProgram
{
private:
    SchemeList sl;
    QueryList ql;
    FactList fl;
    RuleList rl;

public:

    friend std::ostream & operator<<(std::ostream &, const DatalogProgram &);
};

std::ostream & operator<<(std::ostream &out, const DatalogProgram &dp);

#endif //defined __DATALOGPROGRAM_H__

