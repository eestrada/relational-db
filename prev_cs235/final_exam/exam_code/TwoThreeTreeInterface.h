//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once

#include <string>

using namespace std;

class TwoThreeTreeInterface {
public:
	TwoThreeTreeInterface() {}
	virtual ~TwoThreeTreeInterface() {}

	//This class may use a node of your own creation.

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
	 * 	Root (value)
	 *		Left subtree root (value)
	 *			Left left subtree root (value)
	 *			Left middle subtree root (value)
	 *			Left right subtree root (value)
	 *		Middle subtree root (value)
	 *			Middle left subtree root (value)
	 *			Middle middle subtree root (value)
	 *			Middle right subtree root (value)
	 *
	 *		Right subtree root (value)
	 *			Right left subtree root (value)
	 *			Right middle subtree root (value)
	 *			Right right subtree root (value)
	 *
	 */
	virtual string printTree() = 0;
};
