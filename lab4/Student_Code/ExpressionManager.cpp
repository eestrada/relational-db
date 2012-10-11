#include <stack>
#include <string>
#include "ExpressionManager.hpp"

using namespace std;

const string OPEN = "([{";
const string CLOSE = ")]}";

bool is_open(char ch)
{
    return OPEN.find(ch) != string::npos;
}

bool is_close(char ch)
{
    return CLOSE.find(ch) != string::npos;
}

    /*
    * Checks whether an expression is balanced on its parentheses
    * 
    * - The expression will have a space between every number or operator
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
        char next_ch = *iter;

        if(is_open(next_ch)) {chstck.push(next_ch);}
        else if (is_close(next_ch))
        {
            if (chstck.empty()) {balanced = false;}
            else
            {
                char top_ch = chstck.top();
                chstck.pop();
                balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
            }
        }
        ++iter;
    }
    return (balanced && chstck.empty());
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

