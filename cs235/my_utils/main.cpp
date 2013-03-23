#include "edelist.hpp"
#include <iostream>

using ede::list;

using std::cout;
using std::endl;
using std::flush;

int main(void)
{
    list<int> mylist(0,10);

    for(int i = 0; i<10; ++i)
    {
        mylist.push_back(i*10);
    }

    mylist.at(5) = 12345;
    mylist[9] = 54321;

    mylist.insert(1, 67890);

    for(unsigned int i = 0; i < mylist.size(); ++i)
    {
        cout << "Index " << i << ": " << mylist[i] << "\n";
    }

    cout << flush;

    return 0;
}

