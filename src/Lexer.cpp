#include "Lexer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <map>
#include <cctype>

using namespace std;

namespace Lex
{

const map<Kind, string> kmap = {
                                {Kind::COMMA, "COMMA"},
                                {Kind::PERIOD, "PERIOD"},
                                {Kind::Q_MARK, "Q_MARK"},
                                {Kind::LEFT_PAREN, "LEFT_PAREN"},
                                {Kind::RIGHT_PAREN, "RIGHT_PAREN"},
                                {Kind::COLON, "COLON"},
                                {Kind::COLON_DASH, "COLON_DASH"},
                                {Kind::SCHEMES, "SCHEMES"},
                                {Kind::FACTS, "FACTS"},
                                {Kind::RULES, "RULES"},
                                {Kind::QUERIES, "QUERIES"},
                                {Kind::ID, "ID"},
                                {Kind::STRING, "STRING"},
                                {Kind::END_OF_STRM, "END_OF_STRM"},
                               };

const map<Kind, string> strmap = {
                                {Kind::COMMA, ","},
                                {Kind::PERIOD, "."},
                                {Kind::Q_MARK, "?"},
                                {Kind::LEFT_PAREN, "("},
                                {Kind::RIGHT_PAREN, ")"},
                                {Kind::COLON, ":"},
                                {Kind::COLON_DASH, ":-"},
                                {Kind::SCHEMES, "Schemes"},
                                {Kind::FACTS, "Facts"},
                                {Kind::RULES, "Rules"},
                                {Kind::QUERIES, "Queries"},
                               };

Token::operator string() const
{
    ostringstream out;

    string val, k;

    k = kmap.at(this->kind);

    try
    {
        val = strmap.at(this->kind);
    }
    catch (const std::out_of_range &e)
    {
        val = this->value;
    }

    out << "(" << k << ",\"" << val << "\"," << this->lnum << ")";

    return out.str();
}

Lexer::Lexer(const string &file) : in(*(new ifstream(file))), current_line(1), own_stream(true) {}
Lexer::Lexer(istream &i) : in(i), current_line(1), own_stream(false) {}
Lexer::Lexer(unique_ptr<istream> i) : in(*(i.release())), current_line(1), own_stream(true) {}
Lexer::~Lexer()
{
    if(own_stream) delete &in;
}

Token Lexer::next()
{
    if(!cur_tok) cur_tok.reset(new Token);
    *cur_tok = this->lex_next();
    return *cur_tok;
}

Token Lexer::current() const
{
    if(!cur_tok) throw runtime_error("No tokens have been parsed yet.");
    else return *cur_tok;
}

Token Lexer::lex_next()
{
    while(not in.eof())
    {
        int ch = in.peek();

        if (std::isspace(ch))
        {
            this->skip_ws();
        }
        else if (ch == '#')
        {
            this->skip_comment();
        }
        else if (ch == '\'')
        {
            return this->lex_str();
        }
        else if (std::isalpha(ch))
        {
            return this->lex_id();
        }
        else if (std::ispunct(ch))
        {
            return this->lex_punct();
        }
        else if (ch == EOF)
        {
            return this->lex_eof();
        }
        else throw input_error("Unrecognized character.", this->current_line);
    }

    // If we made it down here, then we are at end of file
    return this->lex_eof();
}

void Lexer::check_newline(int c)
{
    if(c == '\n') this->current_line += 1;
}

void Lexer::skip_ws()
{
    for(int c = in.peek(); std::isspace(c); c = in.peek())
    {
        this->check_newline(c);
        in.get();
    }
}

void Lexer::skip_comment()
{
    for(int c = in.peek(); c != '\n'; c = in.peek())
    {
        in.get();
    }
}

Token Lexer::lex_str()
{
    Token retval;
    retval.kind = Kind::STRING;

    retval.value = "";
    in.get(); // discard first single quote

    for(int c = in.peek(); c != '\''; c = in.peek())
    {
        if (c == '\n' || c == EOF) throw input_error("Unterminated string.", this->current_line);
        retval.value += char(c);
        in.get();
    }
    
    in.get(); // discard trailing single quote
    retval.lnum = this->current_line;

    return retval;
}

Token Lexer::lex_keyword(const Token &id)
{
    Token retval = id;

    if(retval.value == strmap.at(Kind::SCHEMES))
        retval.kind = Kind::SCHEMES;
    else if(retval.value == strmap.at(Kind::FACTS))
        retval.kind = Kind::FACTS;
    else if(retval.value == strmap.at(Kind::RULES))
        retval.kind = Kind::RULES;
    else if(retval.value == strmap.at(Kind::QUERIES))
        retval.kind = Kind::QUERIES;

    return retval;
}

Token Lexer::lex_id()
{
    Token retval;
    retval.kind = Kind::ID;

    retval.value = "";

    for(int c = in.peek(); std::isalnum(c); c = in.peek())
    {
        retval.value += char(c);
        in.get();
    }

    retval.lnum = this->current_line;

    return this->lex_keyword(retval);
}

Token Lexer::lex_punct()
{
    int c = in.peek();

    Token retval;
    retval.value = c;
    retval.lnum = this->current_line;

    if(retval.value == strmap.at(Kind::COMMA))
    {
        retval.kind = Kind::COMMA;
        in.get();
    }
    else if(retval.value == strmap.at(Kind::PERIOD))
    {
        retval.kind = Kind::PERIOD;
        in.get();
    }
    else if(retval.value == strmap.at(Kind::Q_MARK))
    {
        retval.kind = Kind::Q_MARK;
        in.get();
    }
    else if(retval.value == strmap.at(Kind::LEFT_PAREN))
    {
        retval.kind = Kind::LEFT_PAREN;
        in.get();
    }
    else if(retval.value == strmap.at(Kind::RIGHT_PAREN))
    {
        retval.kind = Kind::RIGHT_PAREN;
        in.get();
    }
    else if(retval.value == strmap.at(Kind::COLON))
    {
        in.get();
        if(in.peek() != '-')
        {
            retval.kind = Kind::COLON;
        }
        else
        {
            retval.value += in.get();
            retval.kind = Kind::COLON_DASH;
        }
    }
    else throw input_error("Unrecognized punctuation.", this->current_line);

    return retval;
}

Token Lexer::lex_eof()
{
    Token retval;
    retval.kind = Kind::END_OF_STRM;
    retval.lnum = this->current_line;
    return retval;
}

} // end of namespace

