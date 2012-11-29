#include "Node.hpp"
//#include <iostream>

namespace ede
{

Node::Node(int val, Node *p, Node *l, Node *r)
    : data(val), parent(p), left(l), right(r){}

Node::~Node()
{
    delete left;
    delete right;
}

/*
 * Returns the data that is stored in this node
 *
 * @return the data that is stored in this node.
 */
int Node::getData()
{
    return this->data;
}

/*
 * Returns the left child of this node or null if it doesn't have one.
 *
 * @return the left child of this node or null if it doesn't have one.
 */
NodeInterface * Node::getLeftChild()
{
    return static_cast<NodeInterface*>(this->left);
}

/*
 * Returns the right child of this node or null if it doesn't have one.
 *
 * @return the right child of this node or null if it doesn't have one.
 */
NodeInterface * Node::getRightChild()
{
    return static_cast<NodeInterface*>(this->right);
}

/*
 * Returns the height of this node. The height is the number of edges
 * from this node to this nodes farthest child.
 */
int Node::getHeight()
{
    return int();
}

}

