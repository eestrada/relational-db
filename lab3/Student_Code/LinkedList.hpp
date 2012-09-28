#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include <string>
#include "LinkedListInterface.h"
#include "llnode.hpp"

using namespace std;

class LinkedList : public LinkedListInterface
{
private:
    llnode *head;
    llnode *tail;
    unsigned int mysize;
    void printMe();
    llnode* findNode(unsigned int index);

public:

	LinkedList(void){};
	virtual ~LinkedList(void){};
	
	/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Only non-negative values should be added to the list. Do not allow
		duplicate values in the list.
	 */
	virtual void insertHead(int value);

	/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Only non-negative values should be added to the list. Do not allow
		duplicate values in the list.
	 */
	virtual void insertTail(int value);

	/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Only non-negative values should be
		added to the list. Do not allow duplicate values in the list.
	 */
	virtual void insertAfter(int value, int insertionNode);
	
	/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
	 */
	virtual void remove(int value);

	/*
		clear

		Remove all nodes from the list.
	 */
	virtual void clear();

	/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, return -1;
	 */
	virtual int at(int index);

	/*
		size

		Returns the number of nodes in the list.
	 */
	virtual int size();


};

#endif //define __LINKEDLIST_HPP__
