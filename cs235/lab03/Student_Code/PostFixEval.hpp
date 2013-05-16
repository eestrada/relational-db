#ifndef _EXPRESSIONMANAGER_HPP_
#define _EXPRESSIONMANAGER_HPP_

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
        
    }

public:
    int eval(const string &expression);
    {
        while(not operand_stack.empty())
            operand_stack.pop()

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
            }
            else
            {
                throw invalid_argument("Unknown token encountered.");
            }
        }
    }
};

} // End namespace ede

#endif //defined _EXPRESSIONMANAGER_HPP_

