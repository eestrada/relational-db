#if !defined(__DATALOGPROGRAM_H__)
#define __DATALOGPROGRAM_H__
#include "SchemeList.h"
#include "QueryList.h"
#include "FactList.h"
#include "RuleList.h"

class DatalogProgram
{
private:
    SchemeList sl;
    QueryList ql;
    FactList fl;
    RuleList rl;

public:
    DatalogProgram();
    ~DatalogProgram();
};

#endif //defined __DATALOGPROGRAM_H__

