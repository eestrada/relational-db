#ifndef _EXPRESSIONMANAGER_HPP_
#define _EXPRESSIONMANAGER_HPP_

#include <string>
#include <exception>
#include "ExpressionManagerInterface.h"

namespace ede
{
using namespace std;

class Syntax_Error : public exception
{
private:
    string whatStr;

public:
    Syntax_Error(const char* whatErr)
    {
        this->whatStr = whatErr;
    }
    ~Syntax_Error() throw() {}

    virtual const char* what() const throw()
    {
        return this->whatStr.c_str();
    }
};


class ExpressionManager : public ExpressionManagerInterface
{
private:
    void process_operator(char op);
    //int precedence(char op);
    //bool is_operator(char ch);
    stack<char> operator_stack;
    string postfix;

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

} // End namespace ede

#endif //defined _EXPRESSIONMANAGER_HPP_

