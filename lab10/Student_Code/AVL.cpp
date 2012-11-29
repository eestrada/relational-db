#include "AVL.hpp"

#include <iostream>
#include <sstream>

namespace ede
{

AVL::AVL() : root(NULL), head(NULL), tail(NULL){}
AVL::~AVL() {delete(root);}

std::string AVL::recurse()
{
    std::ostringstream retout;
    retout.str("Testing recurse function.");

    return retout.str();
}
//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
 * Returns the root node for this tree
 *
 * @return the root node for this tree.
 */
NodeInterface * AVL::getRootNode()
{
    return static_cast<NodeInterface*>(root);
}

/*
 * Recursive helper function to add values to tree.
 */
bool AVL::addNode(Node *current, int val)
{    
    // Value already exists
    if(val == current->data) return false;
    
    if(val < current->data)
    {
        if(current->left == NULL)
        {
            current->left = new Node(val, current);
            return true;
        }
        else
        {
            return this->addNode(current->left, val);
        }
    }
    else if(val > current->data)
    {
        if(current->right == NULL)
        {
            current->right = new Node(val, current);
            return true;
        }
        else
        {
            return this->addNode(current->right, val);
        }
    }

    throw(-20);
    return false;
}

/*
 * Attempts to add the given int to the BST tree
 *
 * @return true if added
 * @return false if unsuccessful (i.e. the int is already in tree)
 */
bool AVL::add(int data)
{
    if (this->root == NULL) // Check for case of empty tree
    {
        this->root = new Node(data);
        return true;
    }
    
    return this->addNode(root, data);
}

/* 
 * Recursive helper function.
 */
bool AVL::removeNode(Node *current, int val)
{
    // If current is NULL we have hit an empty leaf node. The value to remove 
    // doesn't exist. Return false.
    if (current == NULL)
    {
        return false;
    }
    
    // Value is smaller than current node. Traverse tree to the left.
    if(val < current->data)
    {
        return this->removeNode(current->left, val);
    }
    // Value is smaller than current node. Traverse tree to the right.
    else if(val > current->data)
    {
        return this->removeNode(current->right, val);
    }
    // Value is the same as current node. Remove current node.
    else if(val == current->data)
    {   
        // Leaf node.
        if(current->left == NULL && current->right == NULL)
        {
            if(current == this->root)// Fringe case of leaf node being root.
            {
                this->root = NULL;
            }
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
        // Missing Predecessor
        else if(current->left == NULL && current->right != NULL)
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
        // Check for "Inorder Predecessor"
        else if(current->left != NULL)
        {
            Node *tmp = current->left;

            // Check for "predecessor is left child"
            if(tmp->right == NULL)
            {
                current->data = tmp->data;
                current->left = tmp->left;

                if(current->left != NULL)
                    current->left->parent = current;

                tmp->left = NULL;
                tmp->right = NULL;
                delete(tmp);

                return true;
            }

            // Keep moving to the right until we hit the end of the chain.
            while(tmp->right != NULL)
            {
                tmp = tmp->right;
            }

            // Move value to "deleted" node.
            current->data = tmp->data;

            // Check for "Inorder predecessor with a left child"
            if(tmp->left != NULL)
            {
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                tmp->parent->right = tmp->left;
                tmp->left->parent = tmp->parent;

                tmp->left = NULL;
                tmp->right = NULL;
                delete(tmp);

                return true;
            }

            // Only option left is plain old "inorder predecessor"
            if(tmp->left == NULL)
            {
                
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                tmp->parent->right = NULL;

                tmp->left = NULL;
                tmp->right = NULL;
                delete(tmp);

                return true;
            }

            // If we magically get here, throw an exception.
            throw(-1);
        }

    }

    // If somehow we magically get down here, throw an exception.
    throw(-2);
    return false;
}

/*
 * Attempts to remove the given int from the BST tree
 *
 * @return true if successfully removed
 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
 */
bool AVL::remove(int data)
{
    return this->removeNode(this->root, data);
}

}

