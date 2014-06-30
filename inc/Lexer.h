#ifndef __LEXER_H__
#define __LEXER_H__

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

class lexing_error : public std::runtime_error
{
public:
    lexing_error(const std::string &msg) : std::runtime_error(msg){}
};

class input_error : public lexing_error
{
public:
    input_error(const std::string &msg, intmax_t lnum)
        : lexing_error(msg), ln(lnum){}

    intmax_t line_number() const {return ln;}

private:
    intmax_t ln;
};

enum class Kind : char  {   
                            START_OF_STRM,
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
                            STRING,
                            END_OF_STRM // Only used internally
                        };

struct Token
{
    Token() = default;
    Token(const Token &other) = default;
    Token(Token &&other) = default;

    Token& operator=(const Token &other) = default;
    Token& operator=(Token &&other) = default;

    Kind kind;
    std::string value;
    intmax_t lnum;

    explicit operator std::string() const;
};

class Lexer
{
public: //functions
    Lexer(std::istream &input_stream);
    Token next();
    Token current() const;

private: //functions
    Token lex_next();
    void skip_ws();
    void skip_comment();
    void check_newline(int c);
    Token lex_str();
    Token lex_keyword(const Token &id);
    Token lex_id();
    Token lex_punct();
    Token lex_eof();


private: //data
    std::istream &in;
    intmax_t current_line;
    std::unique_ptr<Token> cur_tok;
};

}

#endif // End include guard
