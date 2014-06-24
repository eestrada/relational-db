#include "Lexer.hpp"
#include <cassert>

using namespace std;

namespace Lex
{
Lexer::Lexer(istream &i) : in(i), current_line(0) {}

Token Lexer::next(void)
{
    assert(!"Member function not yet implemented.");
    Token t;
    return t;
}

}

