#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "RedBlackTree.hpp"

int main(int argc, char** argv)
{
    using namespace std;
    
    RedBlackTree test;
    ifstream testfile("./eestrada_code/test_cases.txt");
    vector<string> strvec;

    string tmp;
    while(!testfile.eof())
    {
        testfile >> tmp;
        strvec.push_back(tmp);
    }

    random_shuffle(strvec.begin(), strvec.end());

    vector<string>::iterator iter;

    tmp = "";
    unsigned int num;

    cout << "Enter the number of items to add: ";
    cin >> num;

    for(iter = strvec.begin(); iter != strvec.begin() + num; ++iter)
    {
       tmp += *iter + ' '; 
    }

    test.addPhrase(tmp);

    cout << test.printTree(true) << endl;
    return 0;
}
