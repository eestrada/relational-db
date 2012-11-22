#include "BSTInterface.h"
#include "BST.hpp"
#include "NodeInterface.h"
#include "Node.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::clog;
using std::endl;

int main(void)
{
    cout << "This is a test" << endl;
    ede::Node mynode;

    cout << mynode.getData() << endl;
    return 0;
}
