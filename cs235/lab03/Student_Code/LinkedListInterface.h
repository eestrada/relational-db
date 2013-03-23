//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once
#include <string>

using namespace std;

class LinkedListInterface
{

public:

	LinkedListInterface(void){};
	virtual ~LinkedListInterface(void){};
	
	/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Only non-negative values should be added to the list. Do not allow
		duplicate values in the list.
	 */
	virtual void insertHead(int value) = 0;

	/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Only non-negative values should be added to the list. Do not allow
		duplicate values in the list.
	 */
	virtual void insertTail(int value) = 0;

	/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Only non-negative values should be
		added to the list. Do not allow duplicate values in the list.
	 */
	virtual void insertAfter(int value, int insertionNode) = 0;
	
	/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
	 */
	virtual void remove(int value) = 0;

	/*
		clear

		Remove all nodes from the list.
	 */
	virtual void clear() = 0;

	/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, return -1;
	 */
	virtual int at(int index) = 0;

	/*
		size

		Returns the number of nodes in the list.
	 */
	virtual int size() = 0;

};
