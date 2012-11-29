#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "NodeInterface.h"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

namespace ede
{

using namespace std;

class Node : public NodeInterface 
{

private:

public:
    static long nodecount;
    
    int data;
    Node *parent, *left, *right;

public:
	Node(): data(), parent(NULL), left(NULL), right(NULL)
    {
    }
	Node(int val, Node *p=NULL, Node *l=NULL, Node *r=NULL): 
        data(val), parent(p), left(l), right(r)
    {
    }

	virtual ~Node()
    {
        delete left;
        delete right;
    }

	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	virtual int getData()
	{
        return this->data;
	}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	virtual NodeInterface * getLeftChild()
	{
        return static_cast<NodeInterface*>(this->left);
	}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	virtual NodeInterface * getRightChild()
	{
        return static_cast<NodeInterface*>(this->right);
	}

	/*
	 * Returns the height of this node. The height is the number of edges
	 * from this node to this nodes farthest child.
	 */
	virtual int getHeight()
    {
        return int();
    }

};

}

#endif // Defined _NODE_HPP_

