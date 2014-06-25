#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <memory>
#include <string>
#include <istream>
#include <exception>
#include <stdexcept>
#include <cstdint>

namespace Lex
{

class end_of_stream : public std::exception 
{
};

class input_error : public std::runtime_error
{
public:
    input_error(const std::string &msg, intmax_t lnum)
        : std::runtime_error(msg), line_number(lnum){}

public:
    const intmax_t line_number;
};

enum class Kind {   
                    COMMA,
                    PERIOD,
                    Q_MARK,
                    LEFT_PAREN,
                    RIGHT_PAREN,
                    COLON,
                    COLON_DASH,
                    SCHEMES,
                    FACTS,
                    RULES,
                    QUERIES,
                    ID,
                    STRING
                };

struct Token
{
    Kind kind;
    std::unique_ptr<std::string> value;
    intmax_t lnum;

    explicit operator std::string();
};

class Lexer
{
public:
    Lexer(std::istream &input_stream);
    Token next(void);

private:
    std::istream &in;
    intmax_t current_line;
};

}

#endif // End include guard
