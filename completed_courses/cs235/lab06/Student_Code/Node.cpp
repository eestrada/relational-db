#include "Node.h"

namespace ede
{

Node::Node(): data(), parent(NULL), left(NULL), right(NULL) {}

Node::Node(int val, Node *p, Node *l, Node *r):
    data(val), parent(p), left(l), right(r) {}

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


}

