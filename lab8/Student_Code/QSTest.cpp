#include <iostream>
#include <string>
#include "QSTest.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::string;


/*
 * Constructor.
 */
QSTest::QSTest(){}

/*
 * Destructor.
 */
QSTest::~QSTest(){}

/*
 * For all methods below, the correctness of an operation is defined in QSInterface.h.
 */

/*
 * testSortAll
 *
 * Returns true if the given QSInterface object correctly sorts given arrays.
 *
 * @param test
 * 		an implementation of the QSInterface class
 * @return
 * 		true if [test] correctly sorts
{
} false otherwise
 */
bool QSTest::testSortAll(QSInterface* test)
{
    int *iarr = new int[20];
    QSInterface &qsref = *test;

    for (int i = 0; i < 20; ++i)
    {
        cout << "Index " << i << ':' << iarr[i] << '\n';
    }

    delete &qsref;

    cout << "Member function \'testSortAll\' has been called!";
    return bool();
}

/*
 * testSort
 *
 * Returns true if the given QSInterface object correctly sorts given subarrays.
 *
 * @param test
 * 		an implementation of the QSInterface class
 * @return
 * 		true if [test] correctly sorts
{
} false otherwise
 */
bool QSTest::testSort(QSInterface* test)
{
    return bool();
}

/*
 * testMedianOfThree
 *
 * Returns true if the given QSInterface object correctly performs median-of-three pivot selection.
 *
 * @param test
 * 		an implementation of the QSInterface class
 * @return
 * 		true if [test] correctly selects a pivot
{
} false otherwise
 */
bool QSTest::testMedianOfThree(QSInterface* test)
{
    return bool();
}

/*
 * testPartition
 *
 * Returns true if the given QSInterface object correctly partitions.
 *
 * @param test
 * 		an implementation of the QSInterface class
 * @return
 * 		true if [test] correctly partitions
{
} false otherwise
 */
bool QSTest::testPartition(QSInterface* test)
{
    return bool();
}

/*
 * testSwap
 *
 * Returns true if the given QSInterface object correctly swaps elements.
 *
 * @param test
 * 		an implementation of the QSInterface class
 * @return
 * 		true if [test] correctly swaps elements
{
} false otherwise
 */
bool QSTest::testSwap(QSInterface* test)
{
    return bool();
}

