#include <iostream>
#include <string>
#include "ExpressionManager.h"

using namespace std;


int main()
{
    ExpressionManager emtest;
    std::string teststr = "Let's check if this works.";

    emtest.isBalanced(teststr);
    std::cout<<"This program has run.\n";
    std::cout<<"Soon it will actually do something useful."<<std::endl;
    return 0;
}
