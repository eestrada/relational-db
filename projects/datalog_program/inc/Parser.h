#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Input.h"
#include "State.h"
#include "Lex.h"
#include <string>
#include <istream>
#include <ostream>

class Parser
{
private:
    Lex lexer;
public:
    Parser() : lexer() {}
    Parser(std::istream &in) : lexer(in) {}
    Parser(const Lex &l) : lexer(l) {}
    Parser(const char* fileName) : lexer(fileName) {}

    std::string toString() const
    {
        return lexer.toString();
    }

    operator std::string() const
    {
        return this->toString();
    }
};

std::ostream& operator<<(std::ostream & out, const Parser &p)
{
    return out << p.toString();
}

#endif // defined PARSER_H

