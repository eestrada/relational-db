#pragma once
#include "PolynomialManagerInterface.h"

using namespace std;

/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	getPolyMan()

	Creates and returns an object whose class extends PolynomialManagerInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Polynomial", you might say, "return new Polynomial();".
*/
class Factory
{
	public:
		static 	PolynomialManagerInterface * getPolyMan();
};
//=======================================================================================
