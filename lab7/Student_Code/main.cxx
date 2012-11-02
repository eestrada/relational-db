#include <string>
#include <vector>
#include <iostream>
#include "Mimic.hpp"

using std::string;
using std::vector;
using std::ostream;

template < typename T >
ostream & operator<<(ostream &stream, const vector<T> &somevec)
{
    for(unsigned int i = 0; i < somevec.size(); ++i)
    {
        stream << somevec[i] << '\n';
    }

    return stream;
}


int main(void)
{
    Mimic test;

    string teststr = "I want to swing I want to boat Boat wants me"; 

    test.createMap(teststr);

    vector<string> list = test.getSuffixList("want to");

    std::cout << "This is the default program" << test.generateText() << std::endl;
}

