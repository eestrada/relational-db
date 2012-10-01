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
    cout << "Completed remove 1." << endl;
    test->insertAfter(4,2);
    cout << "Completed insert after 1." << endl;
    test->printMe();

    test->insertHead(4);
    cout << "Completed insert at head." << endl;
    test->remove(4);
    cout << "Completed remove 2." << endl;
    test->insertTail(5);
    cout << "Completed insert at tail." << endl;
    test->insertHead(2);
    cout << "Completed insert at head 2." << endl;
    test->insertHead(3);
    cout << "Completed insert at head 3." << endl;
    test->insertTail(1);
    cout << "Completed insert at tail 2." << endl;
    test->insertAfter(6,5);
    cout << "Completed insert after 2." << endl;
    test->insertAfter(7,6);
    cout << "Completed insert after 3." << endl;
    test->insertAfter(8,1);
    cout << "Completed insert after 4." << endl;
    test->insertAfter(9,3);
    cout << "Completed insert after 5." << endl;
    test->printMe();

    test->at(1);
    cout << "Completed at 1." << endl;
    test->printMe();

    test->remove(6);
    cout << "Completed remove 3." << endl;
    test->remove(3);
    cout << "Completed remove 4." << endl;
    test->remove(8);
    cout << "Completed remove 5." << endl;
    test->printMe();


    test->clear();
    cout << "Completed clear 1." << endl;
    test->printMe();

    delete(test);

    return 0;

}
