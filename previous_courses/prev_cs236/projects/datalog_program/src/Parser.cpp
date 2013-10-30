#include "Parser.hpp"

Parser::Parser() : lexer(), tvec(lexer.getTokVec()) {}
Parser::Parser(std::istream &in) : lexer(in), tvec(lexer.getTokVec()) {}
Parser::Parser(const char* fileName) : lexer(fileName), tvec(lexer.getTokVec()) {}
Parser::Parser(const Lex &l) : lexer(l), tvec(lexer.getTokVec()) {}

void Parser::ctor_helper()
{
}

std::string Parser::toString() const
{
    return lexer.toString();
}

Parser::operator std::string() const
{
    return this->toString();
}

std::ostream& operator<<(std::ostream & out, const Parser &p)
{
    return out << p.toString();
}
