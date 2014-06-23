#pragma once
#include <iostream>
#include <string>
#include "QSInterface.h"
using namespace std;

/*
 * WARNING: It is expressly forbidden to modify any part of this document, including its name
 */

class QSTestInterface
{
	public:
		QSTestInterface(){}
		virtual ~QSTestInterface(){}

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
		virtual bool testSortAll(QSInterface* test) = 0;

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
		virtual bool testSort(QSInterface* test) = 0;

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
		virtual bool testMedianOfThree(QSInterface* test) = 0;

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
		virtual bool testPartition(QSInterface* test) = 0;

		/*
		 * testSwap
		 *
		 * Returns true if the given QSInterface object correctly swaps elements.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly swaps elements = 0; false otherwise
		 */
		virtual bool testSwap(QSInterface* test) = 0;
};
