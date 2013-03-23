#define USING_EDE_MAIN_CXX
#include <QSTest.hpp>
#include <iostream>

using namespace std;

int main(void)
{
    cout << "Testing\n\n";

    QSTestInterface &test = *(new QSTest());

    QSInterface &qsi = *(new QuickSort());

    test.testSortAll(&qsi);

    return 0;
}
