#include "AVL.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

namespace ede
{

AVL::AVL() : root(NULL), head(NULL), tail(NULL){}
AVL::~AVL() {delete(root);}

class right{};
class left{};

void AVL::syncParents(Node *curParent)
{
/*  
    if(curParent->parent != NULL && curParent->parent->parent != NULL)
    {
        if (curParent->data == curParent->parent->parent->data) return;
    }
*/
    if(curParent == NULL) return;
   

    if(curParent->left != NULL)
    {
        curParent->left->parent = curParent;
        this->syncParents(curParent->left);
    }
    if(curParent->right != NULL)
    {
        curParent->right->parent = curParent;
        this->syncParents(curParent->right);
    }
}

void AVL::rotateRight(Node *parent, Node *child)
{
    if (parent != NULL && child != NULL)
    {
//        std::cerr << "Rotated "<< parent->data << " and "<< child->data <<" to the right!\n";

        Node *pleft = child->right, *cright = parent, *cpar = parent->parent, *ppar = child;

        parent->left = pleft;
        child->right = cright;

/*
        if(pleft != NULL)
        {
            std::cerr << "COOKIES!\n";
            pleft->parent = parent;
        }

        if(cright != NULL)
        {
            std::cerr << "J-DAWGS!\n";
            cright->parent = child;
        }
*/

        child->parent = cpar;
        parent->parent = ppar;

        if(parent == this->root) this->root = child;
        else if (cpar->right == parent) cpar->right = child;
        else if (cpar->left == parent) cpar->left = child;
    }
}
void AVL::rotateLeft(Node *parent, Node *child)
{
    if (parent != NULL && child != NULL)
    {
//        std::cerr << "Rotated "<< parent->data << " and "<< child->data <<" to the left!\n";

        Node *pright = child->left,  *cleft = parent, *cpar = parent->parent, *ppar = child;

        parent->right = pright;
        child->left = cleft;

/*
        if(pright != NULL)
        {
            std::cerr << "MUFFINS!\n";
            pright->parent = parent;
        }

        if(cleft != NULL)
        {
            std::cerr << "BACON PANCAKES!\n";
            cleft->parent = child;
        }
*/

        child->parent = cpar;
        parent->parent = ppar;

        if(parent == this->root) this->root = child;
        else if (cpar->right == parent) cpar->right = child;
        else if (cpar->left == parent) cpar->left = child;
    }
}

void AVL::balanceTree(Node *current)
{
    if(current != NULL)
    {
        int hr = (current->right == NULL) ? -1 : current->right->getHeight();
        int hl = (current->left == NULL) ? -1 : current->left->getHeight();
        int bal = hr - hl;
        
        //std::cerr << "Balance for "<< current->data << ": " << bal << "\n";

        if(bal > 1 && current->right != NULL)
        {
            current->right->parent = current;
            
            this->rotateLeft(current, current->right);
            this->balanceTree(current->parent);
            return;
        }
        if(bal < -1 && current->left != NULL)
        {
            current->left->parent = current;

            this->rotateRight(current, current->left);
            this->balanceTree(current->parent);
            return;
        }

        Node* locPar = current->parent;

        if (locPar != NULL)
        {
            int phr = (locPar->right == NULL) ? -1 : locPar->right->getHeight();
            int phl = (locPar->left == NULL) ? -1 : locPar->left->getHeight();
            int parBal = phr - phl;

            if(bal == 1 && parBal < -1 && locPar->left == current)
            {
//                std::cerr << "Left-right imbalance." << "\n";

                this->rotateLeft(current, current->right);

                //this->syncParents(this->root);
            }
            
            if(bal == -1 && parBal > 1 && locPar->right == current)
            {
                //std::cerr << "Right-left imbalance." << "\n";
            
                this->rotateRight(current, current->left);

                //this->syncParents(this->root);
            }

            //if(locPar->right != NULL) locPar->right->parent = locPar;
            //if(locPar->left != NULL) locPar->left->parent = locPar;
        }

        this->balanceTree(locPar);

        //this->syncParents(this->root);

        return;
    }
}

std::string AVL::recurse()
{
    std::ostringstream retout;

    this->root->outRecurse(retout);

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
            //std::cerr << "New left child is: " << current->left->data << "\n";
            //std::cerr << "Parent is: " << current->data << "\n";
            this->syncParents(this->root);
            
            this->balanceTree(current);
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
            //std::cerr << "New right child is: " << current->right->data << "\n";
            //std::cerr << "Parent is: " << current->data << "\n";
            
            this->syncParents(this->root);
            this->balanceTree(current);
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
    //std::cerr << "Attempting to add: " << data << "\n";
    if (this->root == NULL) // Check for case of empty tree
    {
        this->root = new Node(data);
        return true;
    }
   
    bool added = this->addNode(root, data);
    //if(added) std::cerr << "Added: " << data << std::endl;
    this->syncParents(this->root);
    return added;
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
        this->syncParents(this->root);
    }
    // Value is smaller than current node. Traverse tree to the right.
    else if(val > current->data)
    {
        return this->removeNode(current->right, val);
        this->syncParents(this->root);
    }
    // Value is the same as current node. Remove current node.
    else if(val == current->data)
    {
/*
        std::cerr<< "\tParent: ";
        if(current->parent != NULL) std::cerr << current->parent->data << "\n";
        else std::cerr << "NONE\n";
        
        std::cerr<< "\tL child: ";
        if(current->left != NULL) std::cerr << current->left->data << "\n";
        else std::cerr << "NONE\n";
        
        std::cerr<< "\tR child: ";
        if(current->right != NULL) std::cerr << current->right->data << "\n";
        else std::cerr << "NONE\n";
*/
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
            
//            //std::cerr << "Deleting leaf node: " << current->data << std::endl;
            this->balanceTree(current->parent);

            delete(current);
            return true;
        }
        // Missing Predecessor
        else if(current->left == NULL && current->right != NULL)
        {
            Node *tmp = current->right;
//            //std::cerr << "Deleting missing predessor: " << current->data << std::endl;

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
            
            this->balanceTree(tmp->parent);
            this->syncParents(this->root);
            delete(tmp);
            
            return true;
        }
        // Check for "Inorder Predecessor"
        else if(current->left != NULL)
        {
            Node *tmp = current->left;

            //std::cerr << "\t\tMove left once. Current node is now: " << tmp->data << "\n";

            // Check for "predecessor is left child"
            if(tmp->right == NULL)
            {
                current->data = tmp->data;
                current->left = tmp->left;

                if(current->left != NULL)
                    current->left->parent = current;

                tmp->left = NULL;
                tmp->right = NULL;
                
//                //std::cerr << "Deleting predessor is left child with value of: " << tmp->data << std::endl;
                this->balanceTree(current);
                this->syncParents(this->root);
                delete(tmp);

                return true;
            }

            // Keep moving to the right until we hit the end of the chain.
            while(tmp->right != NULL)
            {
                tmp->right->parent = tmp;
                tmp = tmp->right;
            }

            Node *locPar = tmp->parent;

            //std::cerr << current->data << std::endl;
            // Move value to "deleted" node.
            current->data = tmp->data;
            //std::cerr << current->data << std::endl;
            //if(current->parent != NULL)
                //std::cerr << current->parent->data << std::endl;

            // Check for "Inorder predecessor with a left child"
            if(tmp->left != NULL)
            {
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                tmp->parent->right = tmp->left;
                tmp->left->parent = tmp->parent;

                tmp->left = NULL;
                tmp->right = NULL;

//                //std::cerr << "Deleting inorder predessor with a left child with value of: " << tmp->data << std::endl;
                this->syncParents(this->root);
                this->balanceTree(tmp->parent);
                delete(tmp);

                return true;
            }

            // Only option left is plain old "inorder predecessor"
            if(tmp->left == NULL)
            {
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                
                //std::cerr << "\ttmp address: " << tmp << "\n";
                //std::cerr << "\ttmp->parent->right address: " << tmp->parent->right << "\n";
                
                tmp->parent->right = NULL;

                tmp->left = NULL;
                tmp->right = NULL;
                
                //std::cerr << "Deleting node with parent value: " << tmp->parent->data << "\n";
                //std::cerr << "Deleting node with value: " << tmp->data << "\n";
                this->balanceTree(tmp->parent);
                this->syncParents(this->root);
                delete(tmp);

                return true;
            }
        }

    }
    
    // this should never get called
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
//    std::cerr << "\tAttempting to remove: " << data << "\n";
//
    bool removed = this->removeNode(this->root, data);
//    if(removed) std::cerr << "\tRemoved: " << data << std::endl;
    return removed;
}

}

