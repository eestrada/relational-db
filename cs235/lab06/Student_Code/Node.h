#ifndef _NODE_HPP_
#define _NODE_HPP_
#include "NodeInterface.h"

#if !defined(NULL)
#define NULL 0
#endif

namespace ede
{

class Node : public NodeInterface 
{

public:
	Node();

	Node(int val, Node *p=NULL, Node *l=NULL, Node *r=NULL); 

	virtual ~Node();

	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	virtual int getData();

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	virtual NodeInterface * getLeftChild();

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	virtual NodeInterface * getRightChild();

public:
    int data;
    Node *parent, *left, *right;

};

}

#endif // Defined _NODE_HPP_
