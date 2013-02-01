#if !defined(__DATALOGPROGRAM_H__)
#define __DATALOGPROGRAM_H__

#include "SchemeList.h"
#include "QueryList.h"
#include "FactList.h"
#include "RuleList.h"
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

