#include "Factory.h"
#include "LinkedList.hpp"

//You may add #include statements here

/*
	You will MODIFY THIS DOCUMENT.
*/
//=======================================================================================
/*
	getLinkedList()

	Creates and returns an object whose class extends LinkedListInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "LinkedList", you might say, "return new LinkedList();".
*/
LinkedListInterface * Factory::getLinkedList()
{
	return new LinkedList();//Modify this line
}
