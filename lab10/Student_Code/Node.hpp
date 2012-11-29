#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "NodeInterface.h"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

namespace ede
{

class Node : public NodeInterface 
{

private:

public:
    
    int data;
    Node *parent, *left, *right;

public:
	//Node(): data(), parent(NULL), left(NULL), right(NULL)
    //{
    //}
	Node(int val = int(), Node *p = NULL, Node *l = NULL, Node *r = NULL);

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

	/*
	 * Returns the height of this node. The height is the number of edges
	 * from this node to this nodes farthest child.
	 */
	virtual int getHeight();

};

}

#endif // Defined _NODE_HPP_

