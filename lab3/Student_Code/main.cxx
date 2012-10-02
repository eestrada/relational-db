#include <iostream>
#include <string>
#include "LinkedListInterface.h"
#include "LinkedList.hpp"

using namespace::std;

int main(void)
{
    cout << "Program has started." << endl;
    LinkedList* test = new LinkedList();
    
    cout << "Successfully created linked list." << endl;
    test->printMe();
    test->remove(3);
    cout << "Remove 3." << endl;
    test->insertAfter(4,2);
    cout << "Insert 4 after 2." << endl;
    test->printMe();

    test->insertHead(4);
    cout << "Insert 4 at head." << endl;
    test->remove(4);
    cout << "Remove 4." << endl;
    test->insertTail(5);
    cout << "Insert 5 at tail." << endl;
    test->insertHead(2);
    cout << "Insert 2 at head." << endl;
    test->insertHead(3);
    cout << "Insert 3 at head." << endl;
    test->insertTail(1);
    cout << "Insert 1 at tail." << endl;
    test->insertAfter(6,5);
    cout << "Insert 6 after 5." << endl;
    test->insertAfter(7,6);
    cout << "Insert 7 after 6." << endl;
    test->insertAfter(8,1);
    cout << "Insert 8 after 1." << endl;
    test->insertAfter(9,3);
    cout << "Insert 9 after 3." << endl;
    test->printMe();

    
    cout << "Return value at index 1: " << test->at(1) << endl;
    test->printMe();

    test->remove(6);
    cout << "Remove 6." << endl;
    test->remove(3);
    cout << "Remove 3." << endl;
    test->remove(8);
    cout << "Remove 8." << endl;
    test->printMe();


    test->clear();
    cout << "Clear list." << endl;
    test->printMe();

    delete(test);

    return 0;

}
