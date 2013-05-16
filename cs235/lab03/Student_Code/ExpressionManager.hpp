#ifndef _EXPRESSIONMANAGER_HPP_
#define _EXPRESSIONMANAGER_HPP_

#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <stdexcept>
#include "ExpressionManagerInterface.h"

namespace ede
{

using namespace std;

// Useful Constants
const string OPEN = "([{", CLOSE = ")]}";
const string NUMBERS = "0123456789";
const string OPERATORS = "+-*/%";
const int PRECEDENCE[] = { 1, 1, 2, 2, 2 };

inline long int stol(const string &str)
{
    if(str.find_first_not_of("0123456789") == str.npos)
        return strtol(str.c_str(), NULL, 10);
    else
        throw invalid_argument("Argument not convertable to long int.");
}

inline bool is_int(const string &str)
{
    try
    {
        stol(str);
    }
    catch(exception &e)
    {
        //cerr << e.what() << endl;
        return false;
    }
    return true;
}

inline bool is_open(char ch)
{
    return OPEN.find(ch) != string::npos;
}

inline bool is_close(char ch)
{
    return CLOSE.find(ch) != string::npos;
}

inline bool is_bracket(char ch)
{
    return is_open(ch) or is_close(ch);
}

inline bool is_num(char ch)
{
    return NUMBERS.find(ch) != string::npos;
}

inline bool is_operator(char ch)
{
    return OPERATORS.find(ch) != string::npos;
}

inline int precedence(char op)
{
    return PRECEDENCE[OPERATORS.find(op)];
}

class ExpressionManager : public ExpressionManagerInterface
{
private:
    void process_operator(char op, stack<char> &opstck, string &postfix);
    string i2p_main(string &infixExpression);
    string p2i_main(string &postfixExpression);
    void balance_main(string &expression);
    //int precedence(char op);
    //bool is_operator(char ch);
    //stack<char> operator_stack;
    //string postfix;

public:
    ExpressionManager(){}
    virtual ~ExpressionManager(){}

    /*
    * Checks whether an expression is balanced on its parentheses
    * 
    * - The given expression will have a space between every number or operator
    * 
    * @return true if expression is balanced
    * @return false otherwise
    */

    virtual bool isBalanced(string expression);

    /**
     * Converts a postfix expression into an infix expression
     * and returns the infix expression.
     *
     * - The given postfix expression will have a space between every number or operator.
     * - The returned infix expression must have a space between every number or operator.
     * - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
     * - Check lab requirements for what will be considered invalid.
     *
     * return the string "invalid" if postfixExpression is not a valid postfix expression.
     * otherwise, return the correct infix expression as a string.
     */
    virtual string postfixToInfix(string postfixExpression);
    
    /*
     * Converts an infix expression into a postfix expression 
     * and returns the postfix expression
     * 
     * - The given infix expression will have a space between every number or operator.
     * - The returned postfix expression must have a space between every number or operator.
     * - Check lab requirements for what will be considered invalid.
     * 
     * return the string "invalid" if infixExpression is not a valid infix expression.
     * otherwise, return the correct postfix expression as a string.
     */
    virtual string infixToPostfix(string infixExpression);
    
    /*
     * Evaluates a postfix expression returns the result as a string
     * 
     * - The given postfix expression will have a space between every number or operator.
     * - Check lab requirements for what will be considered invalid.
     * 
     * return the string "invalid" if postfixExpression is not a valid postfix Expression
     * otherwise, return the correct evaluation as a string
     */
    virtual string postfixEvaluate(string postfixExpression);


};

typedef ExpressionManager ExMan;

} // End namespace ede

#endif //defined _EXPRESSIONMANAGER_HPP_

