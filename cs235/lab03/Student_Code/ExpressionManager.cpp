#include <algorithm>
#include "ExpressionManager.hpp"
#include "PostFixEval.hpp"

namespace ede
{

using namespace std;

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
        this->balance_main(expression);
    }
    catch(invalid_argument &e)
    {
        //cerr << e.what();
        return false;
    }

    return true;
}


string ExMan::p2i_main(string &postfixExpression)
{
    istringstream iss(postfixExpression);
    string next, retval;
    stack<string> sstck;
    bool hasop = false;
    int numcnt = 0, opcnt = 0;
    //typedef s string;

    while(iss >> next)
    {
        if(is_int(next))
        {
            sstck.push(next);
            ++numcnt;
        }
        else if(is_operator(next[0]) and sstck.size() > 1)
        {
            hasop = true;
            string tmp = sstck.top(); sstck.pop();
            string infixexp = "( " + tmp + " " + next + " "  + sstck.top() + " )";

            sstck.pop();
            sstck.push(infixexp);

            ++opcnt;
        }
        else
        {
            throw invalid_argument("Unknown token encountered.");
        }
    }

    //string retstr = "invalid";
    if ( abs(numcnt - opcnt) > 1 )
        throw invalid_argument("No operator found.");
    else
        return sstck.top();
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
    string retval = "invalid";

    try
    {
        retval = this->p2i_main(postfixExpression);
        return retval;
    }
    catch(exception &e)
    {
        //cerr << e.what();
        return retval;
    }
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
        this->balance_main(infixExpression);
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
    PostFixEval pfe;
    int retval = 0;

    try
    {
        //this->p2i_main(postfixExpression);
        retval = pfe.eval(postfixExpression);
    }
    catch(invalid_argument &e)
    {
        cerr << e.what() << endl;
        return "invalid";
    }
    catch(...)
    {
        cerr << "Unknown exception was caught." << endl;
        return "invalid";
    }

    ostringstream oss;

    oss << retval;

    return oss.str();
}

} // End namespace ede

