#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "QSTest.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::string;

using namespace std;

/*
 * Constructor.
 */
QSTest::QSTest() : testcases("./Student_Code/testcases_SortAll.txt")
{
    srand(0);
}

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
    vector<int> unsorted, sorted;

    // Initialize vector with random content.
    int middle = RAND_MAX/2;
    for(int i = 0; i < 1000; ++i)
    {
        unsorted.push_back(rand() - middle);
    }

    // Fill sorted with the contents of unsorted
    sorted = unsorted;

    // Sort sorted.
    sort(sorted.begin(), sorted.end());
   
    // Send a pointer to the beginning of my vector, along with its size.
    test->sortAll(&unsorted.front(), unsorted.size());

/*
    // Innocent until proved guilty.
    bool passed = true;
    for (unsigned int i = 0; i < sorted.size(); ++i)
    {
        // To be a correct implementation, sorted and unsorted should always equal eachother.
        if(unsorted[i] != sorted[i])
        {
            // Guess you're guilty.
            passed = false;
            break;
        }
    }
*/

    return (sorted == unsorted);
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

