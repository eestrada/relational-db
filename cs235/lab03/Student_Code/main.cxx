#include <iostream>
#include <fstream>
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.hpp"

using namespace std;

int main(void)
{
    string line;
    ifstream test1 ("./Student_Code/testfiles/test_part1.txt");
    ifstream test2 ("./Student_Code/testfiles/test_part2.txt");
    ifstream test3 ("./Student_Code/testfiles/test_part3.txt");
    ifstream test4 ("./Student_Code/testfiles/test_part4.txt");

    ede::ExpressionManager em;

    bool t1=false,t2=true,t3=false,t4=false;

    if(t1 && test1.is_open())
    {
        cout << "\nTEST FILE 1" << endl;
        while(test1.good())
        {
            getline(test1, line);
            bool balanced = em.isBalanced(line);

            cout <<"Line: \""<< line <<"\" is ";
            cout << (balanced ? "good" : "bad") << "." << endl;
        }
    }

    if(t2 && test2.is_open())
    {
        cout << "\nTEST FILE 2" << endl;
        while(test2.good())
        {
            getline(test2, line);
            string converted = em.infixToPostfix(line);

            cout <<"Line: \""<< line <<"\" converted to Postfix is:\n\t";
            cout << converted << endl;
        }
    }

    if(t3 && test3.is_open())
    { 
        cout << "\nTEST FILE 3" << endl;
        while(test3.good())
        {
            getline(test3, line);
            string converted = em.postfixToInfix(line);

            cout <<"Line: \""<< line <<"\" converted to Infix is:\n\t";
            cout << converted << endl;
        }
    }

    if(t4 && test4.is_open())
    { 
        cout << "\nTEST FILE 4" << endl;
        while(test4.good())
        {
            getline(test4, line);
            string converted = em.postfixEvaluate(line);

            cout <<"Line: \""<< line <<"\" evaluated is: ";
            cout << converted << endl;
        }
    }

    return 0;
}

