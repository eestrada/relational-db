#include <iostream>
#include <string>
#include "LinkedListInterface.h"
#include "LinkedList.hpp"

using namespace::std;

int main(void)
{
    LinkedListInterface* test = new LinkedList();

    test->remove(3);
    test->insertAfter(4,2);

    test->insertHead(4);
    test->remove(4);
    test->insertTail(5);
    test->insertHead(2);
    test->insertHead(3);
    test->insertTail(1);

    test->insertAfter(6,5);
    test->insertAfter(7,6);
    test->insertAfter(8,1);
    test->insertAfter(9,3);

    test->remove(6);
    cout << "made it here 1." << endl;
    test->remove(3);
    test->remove(8);

    cout << "made it here 2." << endl;

    test->clear();

    delete(test);

    return 0;

}
