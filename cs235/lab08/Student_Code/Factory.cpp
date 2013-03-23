#include "Factory.h"
#include "QSTest.hpp"
//You may add #include statments here
using namespace std;

/*
 * Unlike all other documents provided, you may modify this document slightly (but do not change its name)
 */
//=======================================================================================
/*
	createQSTest()

	Creates and returns an object whose class extends QSTestInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "QSTest", you might say, "return new QSTest();".
*/
QSTestInterface* Factory::createQSTest()
{
	return new QSTest();//Modify this line
}
//=======================================================================================
