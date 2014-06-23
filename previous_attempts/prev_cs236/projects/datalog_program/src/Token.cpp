#include "Token.hpp"

#include "Utils.hpp"

#include <string>
#include <sstream>

using namespace std;

Token::Token()
{
    tokenType = NUL;
    lineNumber = 0;
    value = "";
}

Token::Token(TokenType newType, string newValue, unsigned newTokensLineNumber)
{
    tokenType = newType;
    lineNumber = newTokensLineNumber;
    value = newValue;
}

Token::Token(const Token& token)
{
    tokenType = token.tokenType;
    lineNumber = token.lineNumber;
    value = token.value;
}

Token::~Token(){}

TokenType Token::getTokenType() const
{
    return tokenType;
}

unsigned Token::getLineNumber() const
{
    return lineNumber;
}

string Token::getTokensValue() const
{
    return value;
}

string Token::toString() const
{
    string lineNumberString;
    itoa(lineNumberString, lineNumber);
    string retstr = "(";
    retstr += TokenTypeToString(tokenType);
    retstr += ",\"";
    retstr += value;
    retstr += "\",";
    retstr += lineNumberString;
    retstr += ")\n";
    return retstr;
}

bool Token::operator==(const Token& token)
{
    return  (lineNumber == token.lineNumber &&
                  value == token.value &&
                  tokenType == token.tokenType);

}

void Token::setTokenType(const TokenType newTokenType)
{
    tokenType = newTokenType;
}

std::ostream & operator<<(std::ostream &out, const Token &tok)
{
    return (out << tok.toString());
}

