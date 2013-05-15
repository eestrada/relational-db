#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include "ExpressionManager.hpp"

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

void ExMan::balance_main(string &expression)
{
    stack<char> chstck;
    bool balanced = true;
    string::const_iterator iter;

    for(iter=expression.begin(); balanced && (iter != expression.end()); ++iter)
    {
        if(is_open(*iter)) {chstck.push(*iter);}
        else if (is_close(*iter))
        {
            if (chstck.empty()) {balanced = false;}
            else
            {
                char top_ch = chstck.top();
                chstck.pop();
                balanced = OPEN.find(top_ch) == CLOSE.find(*iter);
            }
        }
    }
    if (not (balanced && chstck.empty()))
        {throw invalid_argument("Expression is not balanced.");}
}
    /*
    * Checks whether an expression is balanced on its parentheses
    * 
    * - The expression will have a space between every number or operator
    * 
    * @return true if expression is balanced
    * @return false otherwise
    */

bool ExMan::isBalanced(string expression)
{
    try
    {
        balance_main(expression);
    }
    catch(invalid_argument &e)
    {
        //cerr << e.what();
        return false;
    }

    return true;
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
string ExMan::postfixToInfix(string postfixExpression)
{
    string retstr = "invalid";
    return retstr;
}


void ExMan::process_operator(char op, stack<char> &opstck, string &postfix)
{
    if(opstck.empty()) opstck.push(op);
    else if(precedence(op) > precedence(opstck.top())) opstck.push(op);
    else
    {
        while (!opstck.empty() && (precedence(op) <= precedence(opstck.top())))
        {
           postfix += opstck.top();
           postfix += " ";
           opstck.pop();
        }

        opstck.push(op);
    }
}

void close_bracket(char token, stack<char> &opstck, string &postfix)
{
    int brack_type = CLOSE.find(token);

    while(opstck.top() != OPEN[brack_type])
    {
        postfix += opstck.top();
        postfix += " ";
        opstck.pop();

        if (opstck.empty()) throw invalid_argument("Parenthesis do not match.");
    }

    opstck.pop();
}

string ExMan::i2p_main(string &infixExpression)
{

    //bool valid = true;
    stack<char> opstck;
    string postfix;

    istringstream infix_tokens(infixExpression);
    string next, prev = " ";

    while (infix_tokens >> next)
    {
        if(is_operator(next[0]))
        {
            process_operator(next[0], opstck, postfix);
        }
        else if(is_open(next[0]))
        {
            opstck.push(next[0]);
        }
        else if(is_close(next[0]))
        {
            close_bracket(next[0], opstck, postfix);
        }
        else if (is_int(next))
        {
            //cerr << next << endl;
            //stol(next);

            postfix += next + " ";
            //postfix += " ";
        }
        else
        {
            //There are no other acceptable cases. Throw exception.
            throw invalid_argument("invalid_argument: Unknown token encountered: " + next);
        }

        if (is_operator(prev[0]) and is_operator(next[0]))
            throw invalid_argument("invalid_argument: two adjacent operators without operands.");
        else
            prev = next;
    }

    while (not opstck.empty() and is_operator(opstck.top()))
    {
        char op = opstck.top();
        opstck.pop();
        postfix += op;
        if (not opstck.empty())
            postfix += " ";
    }


    if (not opstck.empty())
        throw invalid_argument("Cannot convert argument.");
/*
    while(!opstck.empty())
    {
        opstck.pop();
    }
*/
    return postfix;
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
string ExMan::infixToPostfix(string infixExpression)
{
    try
    {
        balance_main(infixExpression);
        string retval = this->i2p_main(infixExpression);
        return retval;
    }
    catch (exception &e)
    {
        //cerr << e.what() << endl;
        return "invalid";
    }
    catch (...)
    {
        cerr << "Unknown exception caught!" << endl;
        return "invalid";
    }
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
string ExMan::postfixEvaluate(string postfixExpression)
{
    string retstr = "invalid";
    return retstr;
}

} // End namespace ede

