#ifndef _NODE_HPP_
#define _NODE_HPP_
#include "NodeInterface.h"

#ifndef NULL
#define NULL 0
#endif
namespace ede
{

class Node : public NodeInterface 
{

typedef NodeInterface ni;

public:
    int data;
    Node *left, *right, *parent;

public:
	Node(): data(), left(NULL), right(NULL), parent(NULL){}
	Node(int val, Node *l=NULL, Node *r=NULL, Node *p=NULL): 
        data(val), left(l), right(r), parent(p){}

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

};

};


#endif // Defined _NODE_HPP_
