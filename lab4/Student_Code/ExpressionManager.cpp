#include <iostream>
#include <string>
#include <stack>
#include "ExpressionManager.h"

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
    string::iterator it, end = expression.end();
    stack <char> chstack;

    for(it = expression.begin(); it < end; it++)
    {
        cout << *it << "\n";
    }

    cout<<endl;

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
    return "candy";
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
    return "candy";
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
    return "candy";
}

