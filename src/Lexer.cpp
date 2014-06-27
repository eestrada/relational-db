#include "Lexer.h"
#include <iostream>
#include <sstream>
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
        //cerr << "Caught out of range error.\n";
        val = this->value;
    }

    out << "(" << k << ",\"" << val << "\"," << this->lnum << ")";

    return out.str();
}

Lexer::Lexer(istream &i) : in(i), current_line(1) {}

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
        //cerr << "Current char is: " << char(ch) << endl;

        if (std::isspace(ch))
        {
            //cerr << "about to skip ws\n";
            this->skip_ws();
        }
        if (ch == '#')
        {
            //cerr << "about to skip comment\n";
            this->skip_comment();
        }
        if (ch == '\'')
        {
            //cerr << "about to lex string\n";
            return this->lex_str();
        }
        if (std::isalpha(ch))
        {
            //cerr << "about to lex ID\n";
            return this->lex_id();
        }
        if (std::ispunct(ch))
        {
            //cerr << "about to lex punctuation\n";
            return this->lex_punct();
        }
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
    for(auto c = in.peek(); std::isspace(c); c = in.peek())
    {
        this->check_newline(c);
        in.get();
    }
}

void Lexer::skip_comment()
{
    for(auto c = in.peek(); c != '\n'; c = in.peek())
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

    for(auto c = in.peek(); c != '\''; c = in.peek())
    {
        //if (c == '\n') throw input_error("Newline before end of string.", this->current_line);
        retval.value += c;
        in.get();
    }
    
    in.get(); // discard trailing single quote
    retval.lnum = this->current_line;

    //cerr << "String value is: " << retval.value << endl;

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

    //if(not std::isalpha(c)) throw input_error("ID must start with with alphabetical character.", this->current_line);

    for(auto c = in.peek(); std::isalnum(c); c = in.peek())
    {
        retval.value += c;
        in.get();
    }

    retval.lnum = this->current_line;

    return this->lex_keyword(retval);
}

Token Lexer::lex_punct()
{
    auto c = in.get();

    Token retval;
    retval.value = c;
    retval.lnum = this->current_line;

    if(retval.value == strmap.at(Kind::COMMA))
        retval.kind = Kind::COMMA;
    else if(retval.value == strmap.at(Kind::PERIOD))
        retval.kind = Kind::PERIOD;
    else if(retval.value == strmap.at(Kind::Q_MARK))
        retval.kind = Kind::Q_MARK;
    else if(retval.value == strmap.at(Kind::LEFT_PAREN))
        retval.kind = Kind::LEFT_PAREN;
    else if(retval.value == strmap.at(Kind::RIGHT_PAREN))
        retval.kind = Kind::RIGHT_PAREN;
    else if(retval.value == strmap.at(Kind::COLON))
    {
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
    else 
        throw input_error("Unrecognized punctuation.", this->current_line);

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

