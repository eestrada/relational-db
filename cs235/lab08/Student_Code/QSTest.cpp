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

const int START = 0, END = 24;

const int sortAllCase01[] = {-9, 7, -3, -5, 6, 5, -4, 9, -11, -1, -6, 4, 11, -2, -8, -10, -12, 2, 1, 0, 8, -7, 3, 10};
const int sortAllTrue01[] = {-12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

const int sortCase01[] = {7, 8, -8, -7, 5, -12, -10, 3, 6, 1, 9, 2, -9, -1, -6, 4, -4, 0, -5, -2, 11, -3, -11, 10};
const int sortTrue01[] = {7, 8, -8, -7, -12, -10, -9, -6, -4, -1, 0, 1, 2, 3, 4, 5, 6, 9, -5, -2, 11, -3, -11, 10};

const int medianOfThreeCase01[] = {11, -8, -3, -10, 7, 6, -9, 1, 5, -5, -2, 2, 3, 4, 9, -4, -11, 0, 8, -12, 10, -1, -6, -7};

const int partitionCase01[] = {-6, 3, 0, -5, 4, 2, 1, -7, -3, -4, 10, 5, -12, 11, 7, -11, -1, -8, 9, -10, 8, -2, -9, 6};

const int swapCase01[] = {8, -7, 1, 11, 3, 9, -6, -8, -3, -5, 4, -12, -11, 5, 0, 7, -4, 2, -9, 10, -10, -1, 6, -2};
const int swapTrue01[] = {8, -7, 1, 11, 3, 9, 0, -8, -3, -5, 4, -12, -11, 5, -6, 7, -4, 2, -9, 10, -10, -1, 6, -2};


ostream & operator<<(ostream &out, const vector<int> &intvec)
{
    for(unsigned int i = 0; i < intvec.size(); ++i)
    {
        if(i != 0)
            out << ", "<< intvec[i];
        else
            out << intvec[i];
    }

    out << "\n";

    return out;
}

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

    unsorted.assign(&sortAllCase01[START], &sortAllCase01[END]);
    sorted.assign(&sortAllTrue01[START], &sortAllTrue01[END]);
  
    // Send a pointer to the beginning of my vector, along with its size.
    test->sortAll(&unsorted.front(), unsorted.size());

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
    vector<int> unsorted, sorted;

    unsorted.assign(&sortCase01[START], &sortCase01[END]);
    sorted.assign(&sortTrue01[START], &sortTrue01[END]);

    int left = 4, right = 17;
  
    // Send a pointer to the beginning of my vector, along with its size.
    test->sort(&unsorted.front(), unsorted.size(), left, right);

    
    return (sorted == unsorted);
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
    vector<int> unsorted;

    unsorted.assign(&medianOfThreeCase01[START], &medianOfThreeCase01[END]);
 
    int left = 1, right = 8, middle = (left + right)/2;

    // Send a pointer to the beginning of my vector, along with its size.
    test->medianOfThree(&unsorted.front(), unsorted.size(), left, right);
   
//    cout << unsorted[left] << ", " << unsorted[middle] << ", " << unsorted[right] << endl;

    if(unsorted[left] <= unsorted[middle] && unsorted[middle] <= unsorted[right])
        return true;
    else
        return false;
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
    vector<int> unsorted, original;

    unsorted.assign(&partitionCase01[START], &partitionCase01[END]);
 
    original = unsorted;

    int left = 4, right = 15;
    
    // Send a pointer to the beginning of my vector, along with its size.
    int pivot = test->partition(&unsorted.front(), unsorted.size(), left, right+1);
    
    bool passed = true;

    if (pivot <= left || pivot >= right) passed = false;

    for(int i = left; passed && i < pivot; ++i)
    {
        if(unsorted[i] > unsorted[pivot])
        {
            passed = false;
        }
    }

    for(int i = right; passed && i > pivot; --i)
    {   
        if( unsorted[i] < unsorted[pivot] )
        {
            passed = false;
        }
    }

    return passed;
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
    vector<int> unsorted, sorted;

    unsorted.assign(&swapCase01[START], &swapCase01[END]);
    sorted.assign(&swapTrue01[START], &swapTrue01[END]);
    
    int left = 6, right = 14;

    // Send a pointer to the beginning of my vector, along with its size.
    test->swap(&unsorted.front(), unsorted.size(), left, right);

    bool passed = (sorted[left] == unsorted[left] && sorted[right] == unsorted[right]) ? true : false;

    return passed;
}

