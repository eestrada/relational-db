#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <memory>
#include <string>
#include <istream>
#include <cstdint>

namespace Lex
{
    enum class Kind {kword, ident, colon, lparen, rparen, comma, dot};

    struct Token
    {
        Kind kind;
        std::unique_ptr<std::string> value;
        intmax_t lnum;
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
