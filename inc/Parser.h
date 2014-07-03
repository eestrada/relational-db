#ifndef __PARSER_H__
#define __PARSER_H__
#include "Lexer.h"
#include <memory>
#include <string>
#include <istream>
#include <exception>
#include <stdexcept>
#include <cstdint>

namespace Parse
{

class parsing_error : public std::runtime_error
{
public:
    parsing_error(const std::string &msg) : std::runtime_error(msg){}
};

class syntax_error : public parsing_error
{
public:
    syntax_error(const std::string &msg, intmax_t lnum)
        : parsing_error(msg), ln(lnum){}

    virtual intmax_t line_number() const {return ln;}

private:
    intmax_t ln;
};

class DatalogProgram
{
};

class Rule
{
};

class Predicate
{
};

class Parameter
{
};

class Parser
{
public:
    Parser(std::shared_ptr<Lex::Lexer> l);
private:
    std::shared_ptr<Lex::Lexer> lexer;
};

}

#endif // End include guard
