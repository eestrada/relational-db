//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once

#include <string>

using namespace std;

class RedBlackNodeInterface {

public:
	RedBlackNodeInterface() {}
	virtual ~RedBlackNodeInterface() {}

	/*
	 * Returns the word that is stored in this node
	 *
	 * @return the word that is stored in this node.
	 */
	virtual string getWord() = 0;

	/*
	 * Returns the color of the node. A red node should return 0
	 * and a black node should return 1.
	 *
	 * @return the color of the node
	 */
	virtual int getColor() = 0;

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	virtual RedBlackNodeInterface * getLeftChild() = 0;

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	virtual RedBlackNodeInterface * getRightChild() = 0;

};
