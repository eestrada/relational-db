#include <string>
#include <vector>
#include <iostream>
#include "Mimic.hpp"

using namespace std;




int main(void)
{
    Mimic test;

    string teststr = "I want to swing I want to boat Boat wants me"; 
    string testkey = "want to";

    test.createMap(teststr);

    vector<string> slist = test.getSuffixList(testkey);

    string funinsun = test.generateText();

    cout << funinsun << endl;

    //cout << "Values for \"" << testkey << "\" key:\n" << slist << endl;
}

