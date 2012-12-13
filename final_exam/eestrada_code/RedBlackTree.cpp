#include "RedBlackTree.hpp"
#include "eestrada_exceptions.hpp"
#include <iostream>
#include <sstream>

RedBlackTree::RedBlackTree() : root(NULL) {}
RedBlackTree::~RedBlackTree() { delete root;}

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
 * Returns the root node for this tree
 *
 * @return the root node for this tree.
 */
RedBlackNodeInterface * RedBlackTree::getRootNode(void)
{
    return static_cast<RedBlackNodeInterface*>(root);
}

void RedBlackTree::balance(rbn *current)
{
    //throw ede::unimplemented("void RedBlackTree::balance(rbn*)");
}

bool RedBlackTree::insert(rbn *current, const std::string &val)
{
        // Value already exists
    if(val == current->data) return false;
    
    if(val < current->data)
    {
        if(current->left == NULL)
        {
            rbn *tmp = new rbn(val, RED, current);
            current->setLeftChild(tmp);
            this->balance(current->getLeftChild());

            return true;
        }
        else
        {
            return this->insert(current->left, val);
        }
    }
    else if(val > current->data)
    {
        if(current->right == NULL)
        {
            rbn *tmp = new rbn(val, RED, current);
            current->setRightChild(tmp);
            this->balance(current->getRightChild());
            
            return true;
        }
        else
        {
            return this->insert(current->right, val);
        }
    }

    return false;
}
/*
 * Attempts to add the given word to the tree
 *
 * Addition should be consistent with the instructions found in the exam instructions.
 */
void RedBlackTree::add(std::string data)
{
    if (this->root == NULL) // Check for case of empty tree
    {
        this->root = new rbn(data, BLACK);
        return;
    }
    
    try
    {
        this->insert(root, data);
    }
    catch(ede::unimplemented &e)
    {
        //std::cerr << "While adding value \"" << data << "\" an exception occured:\n\t";
        std::cerr << e.what() << std::endl;
        //throw ue;
    }
}

/*
 * Attempts to add the given string of words to the tree
 *
 * A string of words consists of alphabetical characters, no punctuation marks,
 * and white space as the delimiter separating words. The string should be parsed and
 * each word should be added to the tree.
 */
void RedBlackTree::addPhrase(std::string words)
{
    std::istringstream strin(words);

    std::string tmp;

    while(!strin.eof())
    {
        strin >> tmp;

        this->add(tmp);
    }
}


/*
 * Attempts to remove the given word from the tree
 *
 * Removal should be consistent with the instructions found in the exam instructions.
 */
void RedBlackTree::remove(std::string word)
{
    // Make sure we know this isn't working yet;
    //throw ede::unimplemented("void RedBlackTree::remove(std::string)");
    this->remove(this->root, word);
}


bool RedBlackTree::removeLeaf(rbn *node)
{
    if(node == this->root)// Fringe case of leaf node being root.
    {
        this->root = NULL;
    }
    else
    {
        if(node->getParent()->getLeftChild() == node)
            node->getParent()->setLeftChild(NULL);
        else if(node->getParent()->getRightChild() == node)
            node->getParent()->setRightChild(NULL);
    }
    
    this->balance(node->getParent());

    delete(node);
    return true;
}

//bool RedBlackTree::removeMissingPredecessor(rbn *node, const std::string &val){}

bool RedBlackTree::remove(rbn *current, const std::string &val)
{
    // If current is NULL we have hit an empty leaf node. The value to remove 
    // doesn't exist. Return false.
    if(current == NULL) return false;
    
    // Value is smaller than current node. Traverse tree to the left.
    else if(val < current->getData()) return this->remove(current->getLeftChild(), val);

    // Value is smaller than current node. Traverse tree to the right.
    else if(val > current->getData()) return this->remove(current->getRightChild(), val);

    // Value is the same as current node. Remove it.
    else if(val == current->getData())
    {
        // Leaf node.
        if(current->getLeftChild() == NULL && current->getRightChild() == NULL)
        {
            return this->removeLeaf(current);
        }
        // Missing Predecessor
        else if(current->getLeftChild() == NULL && current->getRightChild() != NULL)
        {
            rbn *tmp = current->getRightChild();

            current->setData(tmp->getData());
            current->setRightChild(tmp->getRightChild());
            current->setLeftChild(tmp->getLeftChild());
            
            if(current->getLeftChild() != NULL)
            {
                current->getLeftChild()->setParent(current);
            }
            if(current->right != NULL)
            {
                current->getRightChild()->setParent(current);
            }
            
            tmp->setLeftChild(NULL);
            tmp->setRightChild(NULL);
            
            this->balance(tmp->getParent());
            
            delete(tmp);
            
            return true;
        }
        // Check for "Inorder Predecessor"
        else if(current->getLeftChild() != NULL)
        {
            rbn *tmp = current->getLeftChild();

            // Check for "predecessor is left child"
            if(tmp->getRightChild() == NULL)
            {
                current->setData(tmp->getData());
                current->setLeftChild(tmp->getLeftChild());

                if(current->getLeftChild() != NULL)
                    current->getLeftChild()->setParent(current);

                tmp->setLeftChild(NULL);
                tmp->setRightChild(NULL);
                
                this->balance(current);
                
                delete(tmp);

                return true;
            }

            // Keep moving to the right until we hit the end of the chain.
            while(tmp->getRightChild() != NULL)
            {
                //tmp->getRightChild()->setParent(tmp);
                tmp = tmp->getRightChild();
            }

            // Move value to "deleted" node.
            current->setData(tmp->getData());

            // Check for "Inorder predecessor with a left child"
            if(tmp->getLeftChild() != NULL)
            {
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                tmp->getParent()->setRightChild(tmp->getLeftChild());
                tmp->getLeftChild()->setParent(tmp->getParent());

                tmp->setLeftChild( NULL );
                tmp->setRightChild( NULL );
                
                this->balance(tmp->getParent());
                delete(tmp);

                return true;
            }

            // Only option left is plain old "inorder predecessor"
            if(tmp->getLeftChild() == NULL)
            {
                // Remove the node whose value was moved to the space of the
                // "deleted" node.
                
                tmp->getParent()->setRightChild(NULL);

                tmp->setLeftChild(NULL);
                tmp->setRightChild(NULL);
                
                this->balance(tmp->getParent());
                
                delete(tmp);

                return true;
            }
        }

    }
    
    // this should never get called
    throw std::exception();
    return false;
}

/*
 * The tree should print in the following format:
 *
 * 	Root (value & color)
 *		Left subtree root (value & color)
 *			Left left subtree root (value & color)
 *			Left right subtree root (value & color)
 *		Right subtree root (value & color)
 *			Right left subtree root (value & color)
 *			Right right subtree root (value & color)
 *
 *	For example:
 *		The tree:
 *
 * 					jumps(b)
 *		brown(r)				quick(r)
 *	The(b)    fox(b)    	over(b)   the(b)
 *                 		lazy(r)
 *
 *		Will print:
 *		jumps(b)
 * 			brown(r)
 * 				The(b)
 * 				fox(b)
 * 			quick(r)
 * 				over(b)
 * 					lazy(r)
 * 				the(b)
 *
 */
std::string RedBlackTree::printTree(void)
{
    std::ostringstream out;
    
    this->printTree(out, this->root, "");
    return out.str();
}

void RedBlackTree::printTree(std::ostream &out, rbn *n, const std::string &ws)
{
    if(n == NULL) return;
    
    out << ws << n->getData() <<'('<< (!n->getColor()?'r':'b') << ")\n";
    std::string new_ws = ws + "  ";

    this->printTree(out, static_cast<rbn*>(n->getLeftChild()), new_ws);
    this->printTree(out, static_cast<rbn*>(n->getRightChild()), new_ws);

    return;
}

