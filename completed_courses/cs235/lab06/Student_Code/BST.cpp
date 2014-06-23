#include "BST.h"

#include <iostream>
#include <stdexcept>

using namespace std;

namespace ede
{

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

BST::BST() : root(NULL){}

BST::~BST() { delete(root); }

/*
 * Returns the root node for this tree
 *
 * @return the root node for this tree.
 */
NodeInterface * BST::getRootNode()
{
    return static_cast<NodeInterface*>(root);
}

/*
 * Recursive helper function to add values to tree.
 */
bool BST::addNode(Node *current, int val)
{    
    // Value already exists
    if(val == current->data) return false;
    
    if(val < current->data)
    {
        if(current->left == NULL)
            { current->left = new Node(val, current); return true; }
        else
            { return this->addNode(current->left, val); }
    }
    else if(val > current->data)
    {
        if(current->right == NULL)
            { current->right = new Node(val, current); return true; }
        else
            { return this->addNode(current->right, val); }
    }

    throw std::runtime_error("Node could not be added properly.");
}

/*
 * Attempts to add the given int to the BST tree
 *
 * @return true if added
 * @return false if unsuccessful (i.e. the int is already in tree)
 */
bool BST::add(int data)
{
    if (this->root == NULL) // Check for case of empty tree
    {
        this->root = new Node(data);
        return true;
    }
    else
    {
        return this->addNode(root, data);
    }
}

/* 
 * Leaf removal helper function.
 */
bool BST::removeLeaf(Node *current, int val)
{
    if(current == this->root)// Fringe case of leaf node being root.
        { this->root = NULL; }
    else
    {
        if(current->parent->left == current)
            current->parent->left = NULL;
        else
            current->parent->right = NULL;
    }

    delete(current);
    return true;
}

/* 
 * Missing Predecessor removal helper function.
 */
bool BST::removeMPred(Node *current, int val)
{
    Node *tmp = current->right;

    current->data = tmp->data;
    current->right = tmp->right;
    current->left = tmp->left;

    if(current->left != NULL)
    {
        current->left->parent = current;
    }
    if(current->right != NULL)
    {
        current->right->parent = current;
    }

    tmp->left = NULL;
    tmp->right = NULL;
    delete(tmp);

    return true;
}

bool BST::removeIPred(Node *current, int val)
{
    Node *tmp = current->left;

    // Check for "predecessor is left child"
    if(tmp->right == NULL)
    {
        current->data = tmp->data; current->left = tmp->left;
        if(current->left != NULL) current->left->parent = current;
        tmp->left = NULL; tmp->right = NULL; delete(tmp);
        return true;
    }

    // Move to the right until the end of the chain.
    while(tmp->right != NULL) tmp = tmp->right;
    current->data = tmp->data; // Move value to "deleted" node.

    // Check for "Inorder predecessor with a left child"
    if(tmp->left != NULL)
    {
        // Remove the node whose value was moved to the space of the "deleted" node.
        tmp->parent->right = tmp->left; tmp->left->parent = tmp->parent;
        tmp->left = NULL; tmp->right = NULL; delete(tmp); // Delete node
        return true;
    }

    // Only option left is plain old "inorder predecessor"
    if(tmp->left == NULL)
    {
        // Remove the node whose value was moved to the space of the "deleted" node.
        tmp->parent->right = NULL;
        tmp->left = NULL; tmp->right = NULL; delete(tmp);
        return true;
    }

    throw std::runtime_error("Node could not be removed."); // We should never reach this.
}

/* 
 * Recursive helper function.
 */
bool BST::removeNode(Node *current, int val)
{
    // Value to remove doesn't exist. Return false.
    if (current == NULL) { return false; }
    // Traverse tree to the left.
    if(val < current->data) { return this->removeNode(current->left, val); }
    // Traverse tree to the right.
    else if(val > current->data) { return this->removeNode(current->right, val); }
    // Remove current node.
    else if(val == current->data)
    {   
        // Remove Leaf node.
        if(current->left == NULL && current->right == NULL)
            { return this->removeLeaf(current, val); }
        // Remove "Missing Predecessor"
        else if(current->left == NULL && current->right != NULL)
            { return this->removeMPred(current, val); }
        // Remove "Inorder Predecessor"
        else if(current->left != NULL)
            { return this->removeIPred(current, val); }
    }
    throw std::runtime_error("Removal failed."); // We should never reach this.
}

/*
 * Attempts to remove the given int from the BST tree
 *
 * @return true if successfully removed
 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
 */
bool BST::remove(int data)
{
    return this->removeNode(this->root, data);
}

}



