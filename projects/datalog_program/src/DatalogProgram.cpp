#include "DatalogProgram.h"

std::ostream & operator<<(std::ostream &out, const DatalogProgram &dp)
{
    out << dp.sl;
    out << dp.ql;
    out << dp.fl;
    out << dp.rl;

    return out;
}
