//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once

#include <string>
#include "RedBlackNodeInterface.h"

using namespace std;

class RedBlackTreeInterface {
public:
	RedBlackTreeInterface() {}
	virtual ~RedBlackTreeInterface() {}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	virtual RedBlackNodeInterface * getRootNode() = 0;

	/*
	 * Attempts to add the given word to the tree
	 *
	 * Addition should be consistent with the instructions found in the exam instructions.
	 */
	virtual void add(string word) = 0;

	/*
	 * Attempts to add the given string of words to the tree
	 *
	 * A string of words consists of alphabetical characters, no punctuation marks,
	 * and white space as the delimiter separating words. The string should be parsed and
	 * each word should be added to the tree.
	 */
	virtual void addPhrase(string words) = 0;

	/*
	 * Attempts to remove the given word from the tree
	 *
	 * Removal should be consistent with the instructions found in the exam instructions.
	 */
	virtual void remove(string word) = 0;

	/*
	 * The tree should print in the following format:
	 *
	 * 	Root (value & color)
	 *		Left subtree root (value & color)
	 *			Left left subtree root (value & color)
	 *			Left right subtree root (value & color)
	 *		Right subtree root (value & color)
	 *			Right left subtree root (value & color)
	 *			Right right subtree root (value & color)
	 *
	 *	For example:
	 *		The tree:
	 *
	 * 					jumps(b)
	 *		brown(r)				quick(r)
	 *	The(b)    fox(b)    	over(b)   the(b)
	 *                 		lazy(r)
	 *
	 *		Will print:
	 *		jumps(b)
	 * 			brown(r)
	 * 				The(b)
	 * 				fox(b)
	 * 			quick(r)
	 * 				over(b)
	 * 					lazy(r);
	 * 				the(b)
	 *
	 */
	virtual string printTree() = 0;
};
