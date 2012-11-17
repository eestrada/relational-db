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


const int sortAllCase01[] = {6, -4, 5, -5, 10, 4, -1, 8, 7, 3};
const int sortAllTrue01[] = {-5, -4, -1, 3, 4, 5, 6, 7, 8, 10};
const int sortAllCase02[] = {-7, 1, -4, 10, -3, 9, -10, 2, -8, -1};
const int sortAllTrue02[] = {-10, -8, -7, -4, -3, -1, 1, 2, 9, 10};

const int sortCase01[] = {-6, -4, 1, 3, 0, -10, -1, -2, -3, 8};
const int sortTrue01[] = {-6, -4, -10, -2, -1, 0, 1, 3, -3, 8};
const int sortCase02[] = {-7, -8, 5, -4, -6, -2, 6, 9, 8, -5};
const int sortTrue02[] = {-7, -8, 5, -4, -6, -2, 6, 9, 8, -5};

const int medianOfThreeCase01[] = {-6, 1, -1, -10, -11, -2, 10, -5, -3, 2};
const int medianOfThreeTrue01[] = {-6, 1, -1, -10, -11, -2, 10, -5, -3, 2};
const int medianOfThreeCase02[] = {3, -9, 3, 9, -9, 10, 5, 4, 10, -2};
const int medianOfThreeTrue02[] = {3, -9, 3, 9, -9, 10, 5, 4, 10, -2};

const int partitionCase01[] = {-2, -1, -9, -3, -8, 8, -4, -7, -10, -6};
const int partitionTrue01[] = {-2, -1, -9, -3, -8, 8, -4, -7, -10, -6};
const int partitionCase02[] = {-5, 2, -2, -4, 10, 9, -7, -10, 5, 0};
const int partitionTrue02[] = {-5, 2, -2, -4, 10, 9, -7, -10, 5, 0};

const int swapCase01[] = {4, -9, 4, 9, 7, -5, -1, -10, -4, -3};
const int swapTrue01[] = {4, -1, 4, 9, 7, -5, -9, -10, -4, -3};
const int swapCase02[] = {5, -8, 0, 0, 6, 5, 6, 3, 6, -10};
const int swapTrue02[] = {5, -8, 0, 0, 6, 5, 6, 3, 6, -10};


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

    unsorted.assign(&sortAllCase01[0], &sortAllCase01[10]);
    sorted.assign(&sortAllTrue01[0], &sortAllTrue01[10]);
  
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

    unsorted.assign(&sortCase01[0], &sortCase01[10]);
    sorted.assign(&sortTrue01[0], &sortTrue01[10]);
  
    // Send a pointer to the beginning of my vector, along with its size.
    test->sort(&unsorted.front(), unsorted.size(), 2, 7);

//    cout << sorted << unsorted << endl;

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

    unsorted.assign(&medianOfThreeCase01[0], &medianOfThreeCase01[10]);
  
    // Send a pointer to the beginning of my vector, along with its size.
    test->medianOfThree(&unsorted.front(), unsorted.size(), 1, 8);

    int left, right, middle;
    
    left = unsorted[1];
    right = unsorted[8];
    middle = unsorted[(1+8)/2];
   
//    cout << left << ", " << middle << ", " << right << endl;

    if(left <= middle && middle <= right)
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
    vector<int> unsorted;

    unsorted.assign(&partitionCase01[0], &partitionCase01[10]);
  
    int left = 1, right = 8, middle;
    
    // Send a pointer to the beginning of my vector, along with its size.
    int pivot = test->partition(&unsorted.front(), unsorted.size(), left, right);
    
    middle = unsorted[pivot];

//    cout << "The pivot index is: " << pivot << "\n";
//    cout << "The pivot value is: " << middle << "\n";

    bool passed = true;

    for(int i = left; i < pivot; ++i)
    {
//        cout << "Compare " << unsorted[i] << " with " << middle << "\n";
        if(unsorted[i] > middle)
        {
//            cout << "Make passed false.\n";
            passed = false;
        }
    }

    for(int i = right; i > pivot; --i)
    {
//        cout << "Compare " << middle << " with " << unsorted[i] << "\n";
        if(middle > unsorted[i])
        {
//            cout << "Make passed false.\n";
            passed = false;
        }
    }
   
//    cout << unsorted << endl;
    
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

    unsorted.assign(&swapCase01[0], &swapCase01[10]);
    sorted.assign(&swapTrue01[0], &swapTrue01[10]);
    
    int left = 1, right = 6;

    // Send a pointer to the beginning of my vector, along with its size.
    test->swap(&unsorted.front(), unsorted.size(), left, right);

//    cout << sorted << unsorted << endl;

    return (sorted == unsorted);
}

