#ifndef _POSTFIXEVAL_HPP_
#define _POSTFIXEVAL_HPP_

#include "ExpressionManager.hpp"

namespace ede
{

using namespace std;

class PostFixEval
{
private:
    stack<int> operand_stack;

    int eval_op(char op)
    {
        if(operand_stack.empty())
            throw invalid_argument("Stack is empty.");
        int rhs = operand_stack.top();
        operand_stack.pop();
        if(operand_stack.empty())
            throw invalid_argument("Stack is empty.");
        int lhs = operand_stack.top();
        operand_stack.pop();
        int result = 0;

        switch(op)
        {
        case '-' :  result = lhs - rhs;
                    break;
        case '+' :  result = lhs + rhs;
                    break;
        case '*' :  result = lhs * rhs;
                    break;
        case '/' :  result = lhs / rhs;
                    break;
        case '%' :  result = lhs % rhs;
                    break;
        default  :  throw invalid_argument("Unknown operator symbol.");
                    break;
        }

        return result;
    }

public:
    int eval(const string &expression)
    {
        while(!operand_stack.empty())
            operand_stack.pop();

        istringstream tokens(expression);
        char next_char;

        while(tokens >> next_char)
        {
            if ( isdigit(next_char) )
            {
                tokens.putback(next_char);
                int value;
                tokens >> value;
                operand_stack.push(value);
            }
            else if ( is_operator(next_char) )
            {
                int result = this->eval_op(next_char);
                operand_stack.push(result);
            }
            else
            {
                throw invalid_argument("Unknown token encountered.");
            }
        }
        if (!operand_stack.empty())
        {
            int answer = operand_stack.top();
            operand_stack.pop();
            if (operand_stack.empty())
            {
                return answer;
            }
            else
            {
                throw invalid_argument("Stack should be empty.");
            }
        }
        else
        {
            throw invalid_argument("Stack is empty.");
        }
    }
};

} // End namespace ede

#endif //defined _EXPRESSIONMANAGER_HPP_

