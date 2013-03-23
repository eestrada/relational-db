#pragma once
#include "TwoThreeTreeInterface.h"

using namespace std;

/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	getTwoThreeTree()

	Creates and returns an object whose class extends TwoThreeTreeInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "TwoThreeTree", you might say, "return new TwoThreeTree();".

	This method should return NULL or 0 if you do not intent to do the extra credit
*/
class TwoThreeTreeFactory
{
	public:
		static TwoThreeTreeInterface * getTwoThreeTree();
};
//=======================================================================================
