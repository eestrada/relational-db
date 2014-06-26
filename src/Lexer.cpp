#include "Lexer.h"
#include <sstream>
#include <cassert>
#include <map>

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

Token Lexer::next(void)
{
    assert(!"Member function not yet implemented.");
    Token t;
    return t;
}

}

