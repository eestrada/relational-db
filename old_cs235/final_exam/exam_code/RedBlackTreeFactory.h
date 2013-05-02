#pragma once
#include "RedBlackTreeInterface.h"

using namespace std;

/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	getRedBlackTree()

	Creates and returns an object whose class extends RedBlackTreeInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "RedBlackTree", you might say, "return new RedBlackTree();".
*/
class RedBlackTreeFactory
{
	public:
		static RedBlackTreeInterface * getRedBlackTree();
};
//=======================================================================================
