#ifndef PARSER_H
#define PARSER_H

#include "Token.hpp"
#include "Input.hpp"
#include "State.hpp"
#include "Lex.hpp"
#include <string>
#include <istream>
#include <ostream>

class Parser
{
private:
    Lex lexer;
    std::vector<Token> tvec;
    void ctor_helper();

public:
    Parser();
    Parser(std::istream &in);
    Parser(const char* fileName);
    Parser(const Lex &l);
    std::string toString() const;
    operator std::string() const;
};

std::ostream& operator<<(std::ostream & out, const Parser &p);

#endif // defined PARSER_H

