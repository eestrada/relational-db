#include <stack>
#include <string>
#include "ExpressionManager.hpp"

using namespace std;

    /*
    * Checks whether an expression is balanced on its parentheses
    * 
    * - The given expression will have a space between every number or operator
    * 
    * @return true if expression is balanced
    * @return false otherwise
    */

bool ExpressionManager::isBalanced(string expression)
{
    stack<char> chstck;

    bool balanced = true;

    string::const_iterator iter = expression.begin();

    while (balanced && (iter != expression.end()))
    {
        char test = *iter;
        switch (test)
        {
            case '(':
            case '{':
            case '[':
                chstck.push(*iter);
                ++iter;
                break;

            case ')': 
                if(chstck.top() == '(') {chstck.pop();}
                else {balanced = false;}
                ++iter;
                break;

            case '}': 
                if(chstck.top() == '{') {chstck.pop();}
                else {balanced = false;}
                ++iter;
                break;

            case ']': 
                if(chstck.top() == '[') {chstck.pop();}
                else {balanced = false;}
                ++iter;
                break;

            default:
                ++iter;
        }        
    }

    if(chstck.size() > 0) {balanced = false;}

    return balanced;
}



void ExpressionManager::process_operator(char op, stack<char> &op_stack)
{
    return;
}

int ExpressionManager::precedence(char op)
{
    return -1;
}

bool ExpressionManager::is_operator(char ch)
{
    return false;
}
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
string ExpressionManager::postfixToInfix(string postfixExpression)
{
    stack<char> operator_stack;
    string postfix;

    string::const_iterator iter = postfixExpression.begin();

    while(iter != postfixExpression.end())
    {
        continue;
    }

    string retstr = "invalid";
    return retstr;
}
    
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
string ExpressionManager::infixToPostfix(string infixExpression)
{ 
    string retstr = "invalid";
    return retstr;
}   
    /*
     * Evaluates a postfix expression returns the result as a string
     * 
     * - The given postfix expression will have a space between every number or operator.
     * - Check lab requirements for what will be considered invalid.
     * 
     * return the string "invalid" if postfixExpression is not a valid postfix Expression
     * otherwise, return the correct evaluation as a string
     */
string ExpressionManager::postfixEvaluate(string postfixExpression)
{ 
    string retstr = "invalid";
    return retstr;
}

