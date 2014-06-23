#if !defined(__DATALOGPROGRAM_H__)
#define __DATALOGPROGRAM_H__

#include "SchemeList.hpp"
#include "QueryList.hpp"
#include "FactList.hpp"
#include "RuleList.hpp"
#include "Token.hpp"
#include "Lex.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>

class DatalogProgram
{
private:
    Lex lexer;
    std::vector<Token> tvec;

    SchemeList sl;
    QueryList ql;
    FactList fl;
    RuleList rl;

public:

    DatalogProgram();
    DatalogProgram(std::istream &in);
    DatalogProgram(const char* fileName);
    DatalogProgram(const Lex &l);

    void parseSchemes(std::istream &in, const std::string &str);
    void parseQueries(std::istream &in, const std::string &str);
    void parseFacts(std::istream &in, const std::string &str);
    void parseRules(std::istream &in, const std::string &str);

    std::string toString() const;
};

std::ostream & operator<<(std::ostream &out, const DatalogProgram &dp);

#endif //defined __DATALOGPROGRAM_H__

