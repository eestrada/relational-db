#include "QSTestInterface.h"
#pragma once
/*
 * WARNING: It is expressly forbidden to modify any part of this document, including its name
 */
//=======================================================================================
/*
	createQSTest()

	Creates and returns an object whose class extends QSTestInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "QSTest", you might say, "return new QSTest();".
*/
class Factory
{
	public:
		static QSTestInterface* createQSTest();
};

//=======================================================================================
