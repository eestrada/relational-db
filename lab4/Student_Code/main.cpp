#include <iostream>
#include <string>
#include "ExpressionManager.h"

using namespace std;


int main()
{
    ExpressionManager emtest;
    string teststr = "Let's check if this works.";

    bool test = emtest.isBalanced(teststr);
    cout << "Returned value: " << boolalpha << test << endl;
    return 0;
}
