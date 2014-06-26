#include "Lexer.h"
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

const map<Kind, string> valmap = {
                                {Kind::COMMA, "\",\""},
                                {Kind::PERIOD, "\".\""},
                                {Kind::Q_MARK, "\"?\""},
                                {Kind::LEFT_PAREN, "\"(\""},
                                {Kind::RIGHT_PAREN, "\")\""},
                                {Kind::COLON, "\":\""},
                                {Kind::COLON_DASH, "\":-\""},
                                {Kind::SCHEMES, "\"Schemes\""},
                                {Kind::FACTS, "\"Facts\""},
                                {Kind::RULES, "\"Rules\""},
                                {Kind::QUERIES, "\"Queries\""},
                               };

Token::operator string()
{
    ostringstream out;

    string val, k;

    k = kmap.at(this->kind);

    if(this->value) val = "\"" + *(this->value) + "\"";
    else val = valmap.at(this->kind);

    out << "(" << k << "," << val << "," << this->lnum << ")";

    return out.str();
}

Lexer::Lexer(istream &i) : in(i), current_line(0) {}

Token Lexer::next()
{
    if(!cur_tok) cur_tok.reset(new Token);
    *cur_tok = this->lex_next();
    return *cur_tok;
}

Token Lexer::lex_next()
{
    while(not in.eof())
    {
        int ch = in.peek();

        if (std::isspace(ch)) this->skip_ws();
        if (ch == '#') this->skip_comment();
        if (ch == '\'') return this->lex_quote();
        if (std::isalpha(ch)) return this->lex_id();
        if (std::ispunct(ch)) return this->lex_punct();
    }

    // If we made it down here, then we are at end of file
    return this->lex_eof();
}

Token Lexer::lex_eof()
{
    Token retval;
    retval.kind = Kind::END_OF_STRM;
    retval.lnum = this->current_line;
    return retval;
}

} // end of namespace

