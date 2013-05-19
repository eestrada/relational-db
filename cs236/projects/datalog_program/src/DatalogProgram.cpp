#include "DatalogProgram.hpp"


DatalogProgram::DatalogProgram() : lexer(), tvec(lexer.getTokVec()) {}
DatalogProgram::DatalogProgram(std::istream &in) : lexer(in), tvec(lexer.getTokVec()) {}
DatalogProgram::DatalogProgram(const char* fileName) : lexer(fileName), tvec(lexer.getTokVec()) {}
DatalogProgram::DatalogProgram(const Lex &l) : lexer(l), tvec(lexer.getTokVec()) {}

void DatalogProgram::parseSchemes(std::istream &in, const std::string &str="")
{
}

void DatalogProgram::parseQueries(std::istream &in, const std::string &str="")
{
}

void DatalogProgram::parseFacts(std::istream &in, const std::string &str="")
{
}

void DatalogProgram::parseRules(std::istream &in, const std::string &str="")
{
}

std::string DatalogProgram::toString() const
{
    return lexer.toString();
}

std::ostream & operator<<(std::ostream &out, const DatalogProgram &dp)
{
    out << dp.toString();

    return out;
}

