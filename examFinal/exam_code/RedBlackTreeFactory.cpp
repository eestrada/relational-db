#include "RedBlackTreeFactory.h"
#include "RedBlackTree.hpp"
//You may add #include statements here

/*
	You will MODIFY THIS DOCUMENT.
*/
//=======================================================================================
/*
	getRedBlackTree()

	Creates and returns an object whose class extends RedBlackTreeInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "RedBlackTree", you might say, "return new RedBlackTree();".
*/
RedBlackTreeInterface * RedBlackTreeFactory::getRedBlackTree()
{
	return new RedBlackTree();//Modify this line
}
