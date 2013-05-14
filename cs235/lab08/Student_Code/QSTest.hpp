#pragma once
#include <iostream>
#include <fstream>
#include <string>

/* 
 * Include my quicksort class if I am compiling with my main file, 
 * other wise just include the QSInterface.
 *
 */
#if defined(USING_EDE_MAIN_CXX)
#include "QuickSort.hpp"
#else
#include "QSInterface.h"
#endif

#include "QSTestInterface.h"
using namespace std;

class QSTest : public QSTestInterface
{
    private:
    ifstream testcases;
	public:
		QSTest();
		virtual ~QSTest();

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
		 * 		true if [test] correctly sorts; false otherwise
		 */
		virtual bool testSortAll(QSInterface* test);

		/*
		 * testSort
		 *
		 * Returns true if the given QSInterface object correctly sorts given subarrays.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly sorts; false otherwise
		 */
		virtual bool testSort(QSInterface* test);

		/*
		 * testMedianOfThree
		 *
		 * Returns true if the given QSInterface object correctly performs median-of-three pivot selection.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly selects a pivot; false otherwise
		 */
		virtual bool testMedianOfThree(QSInterface* test);

		/*
		 * testPartition
		 *
		 * Returns true if the given QSInterface object correctly partitions.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly partitions; false otherwise
		 */
		virtual bool testPartition(QSInterface* test);

		/*
		 * testSwap
		 *
		 * Returns true if the given QSInterface object correctly swaps elements.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly swaps elements; false otherwise
		 */
		virtual bool testSwap(QSInterface* test);
};