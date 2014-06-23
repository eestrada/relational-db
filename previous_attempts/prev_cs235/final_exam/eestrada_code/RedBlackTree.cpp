#include "RedBlackTree.hpp"
#include "eestrada_exceptions.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

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
    rbn *parent = current->getParent();
    if(parent != NULL && parent->getColor() != BLACK)
    {
        //rbn *grandparent = parent->getParent();

        //if(grandparent->getLeftChild() != NULL)

        return;
    }

    // If we made it here then there is no balancing to do.
    return;
}

void RedBlackTree::rotateRight(rbn *node)
{
    std::cerr << "Rotate right! With value of: " << node->getData() << std::endl;
    rbn *lc = node->getLeftChild();

    rbn *pleft = lc->getRightChild();
    rbn *cright = node;
    rbn *cparent = node->getParent();
    rbn *pparent = lc;

    node->setLeftChild(pleft);
    lc->setRightChild(cright);

    lc->setParent(cparent);
    node->setParent(pparent);
    
    if(this->root == node) this->root = lc;
    else if (cparent->getRightChild() == node) cparent->setRightChild(lc);
    else if (cparent->getLeftChild() == node) cparent->setLeftChild(lc);
    else assert(false && "Rotate right failed. Parent does not know child.");
}

void RedBlackTree::rotateLeft(rbn *node)
{
    std::cerr << "Rotate left! With value of: " << node->getData() << std::endl;
    rbn *rc = node->getRightChild();

    rbn *pright = rc->getLeftChild();
    rbn *cleft = node;
    rbn *cparent = node->getParent();
    rbn *pparent = rc;

    node->setRightChild(pright);
    rc->setLeftChild(cleft);

    rc->setParent(cparent);
    node->setParent(pparent);
   
    std::cerr << this->root << ": " << node << ": "<< cparent << std::endl;
    if(this->root == node) this->root = rc;
    else if (cparent->getRightChild() == node) cparent->setRightChild(rc);
    else if (cparent->getLeftChild() == node) cparent->setLeftChild(rc);
    else //assert(false && "Rotate left failed. Parent does not know child.");
    {
        std::cerr << cparent->getLeftChild() << std::endl;
        std::cerr << cparent->getRightChild() << std::endl;
        std::cerr << node << std::endl;
        std::cerr << rc << std::endl;
    }
}

bool RedBlackTree::insert(rbn *current, const std::string &val)
{
    bool retval = false;

    if(val == current->getData()) return retval;// Value already exists

    if(val < current->getData())
    {
        if(current->getLeftChild() == NULL)
        {
            rbn *tmp = new rbn(val, RED, current);
            current->setLeftChild(tmp);

            return true;
        }
        else
        {
            rbn *l = current->getLeftChild(), *r = current->getRightChild();

            color lclr = (l) ? color(l->getColor()) : BLACK;
            color rclr = (r) ? color(r->getColor()) : BLACK;
            
            if(lclr == RED && rclr == RED)
            {
                current->setColor(RED);
                l->setColor(BLACK);
                r->setColor(BLACK);
            }

            retval = this->insert(current->getLeftChild(), val);

            //l = current->getLeftChild();
            if(l != NULL && l->getColor() == RED)
            {
                rbn *lgc = l->getLeftChild(), *rgc = l->getRightChild();

                if(lgc != NULL && lgc->getColor() == RED)
                {
                    l->setColor(BLACK);
                    current->setColor(RED);
                    this->rotateRight(current);
                }
                else if(rgc != NULL && rgc->getColor() == RED)
                {
                    rgc->setColor(BLACK);
                    current->setColor(RED);

                    std::cerr << "Am I causing the error? ";
                    std::cerr << l->getData() << std::endl;
                    this->rotateLeft(l);
                    this->rotateRight(current);
                }
            }
        }
    }
    else if(val > current->getData())
    {
        if(current->getRightChild() == NULL)
        {
            rbn *tmp = new rbn(val, RED, current);
            current->setRightChild(tmp);
            
            return true;
        }
        else
        {
            rbn *l = current->getLeftChild(), *r = current->getRightChild();

            color lclr = (l) ? color(l->getColor()) : BLACK;
            color rclr = (r) ? color(r->getColor()) : BLACK;
            
            if(lclr == RED && rclr == RED)
            {
                current->setColor(RED);
                l->setColor(BLACK);
                r->setColor(BLACK);
            }

            retval = this->insert(r, val);

            //r = current->getRightChild();
            if(r != NULL && r->getColor() == RED)
            {
                rbn *lgc = r->getLeftChild(), *rgc = r->getRightChild();

                if(rgc != NULL && rgc->getColor() == RED)
                {
                    r->setColor(BLACK);
                    current->setColor(RED);
                    this->rotateLeft(current);
                }
                else if(lgc != NULL && lgc->getColor() == RED)
                {
                    lgc->setColor(BLACK);
                    current->setColor(RED);
                    
                    //r = current->getRightChild();
                    
                    this->rotateRight(r);
                    std::cerr << "No, I'm causing the error. ";
                    std::cerr << current->getData() << std::endl;
                    this->rotateLeft(current);
                }
            }
        }
    }

    if(this->root == current) current->setColor(BLACK);

    return retval;
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
    else
    {
        this->insert(this->root, data);
        this->root->setColor(BLACK);
        return;
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

bool RedBlackTree::removeMissingPred(rbn *current)
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

bool RedBlackTree::rmPredIsLeftChild(rbn *node)
{
    rbn *lchild = node->getLeftChild();

    node->setData(lchild->getData());
    node->setLeftChild(lchild->getLeftChild());
    rbn *llc = node->getLeftChild();

    if(llc != NULL)
    {
        llc->setParent(node);
    }

    lchild->setLeftChild(NULL);
    lchild->setRightChild(NULL);
    delete(lchild);
    
    this->balance(node);
    return true;
}

bool RedBlackTree::rmPredHasLeftChild(rbn *node)
{
    // Remove the node whose value was moved to the space of the
    // "deleted" node.
    rbn *parent = node->getParent();
    rbn *left = node->getLeftChild();

    parent->setRightChild(left);
    left->setParent(parent);

    node->setLeftChild( NULL );
    node->setRightChild( NULL );
    delete(node);

    this->balance(parent);
    return true;
}

bool RedBlackTree::removeInorderPred(rbn *node)
{
    // Remove the node whose value was moved to the space of the
    // "deleted" node.

    rbn *parent = node->getParent();
    
    parent->setRightChild(NULL);

    node->setLeftChild(NULL);
    node->setRightChild(NULL);
    delete(node);

    this->balance(parent);
    return true;
}

bool RedBlackTree::removeValue(rbn *current)
{
    if(current->getLeftChild() == NULL && current->getRightChild() == NULL)// Leaf node.
        { return this->removeLeaf(current); }
    else if(current->getLeftChild() == NULL && current->getRightChild() != NULL)// Missing Predecessor
        { return this->removeMissingPred(current); }
    else if(current->getLeftChild() != NULL)// Check for "Inorder Predecessor"
    {
        rbn *tmp = current->getLeftChild();

        if(tmp->getRightChild() == NULL)// Check for "predecessor is left child"
            { return this->rmPredIsLeftChild(current); }

        while(tmp->getRightChild() != NULL)// Move right until end of the chain.
            { tmp = tmp->getRightChild(); }

        current->setData(tmp->getData());// move value to "deleted" node.

        if(tmp->getLeftChild() != NULL)// check for "inorder predecessor with a left child"
            { return this->rmPredHasLeftChild(tmp); }

        if(tmp->getLeftChild() == NULL)// Only option left is "inorder predecessor"
            { return this->removeInorderPred(tmp); }
    }
    assert(0 && "We found the value, but failed to remove it properly.");
}

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
        return this->removeValue(current);
    }
    
    // This should never get called
    assert(0 && "Our recursive remove function failed.");
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
std::string RedBlackTree::printTree(bool printsides)
{
    std::ostringstream out;
    
    this->printTree(out, this->root, "", printsides-1);
    return out.str();
}

std::string RedBlackTree::printTree() {return this->printTree(false);}

void RedBlackTree::printTree(std::ostream &out, rbn *node,
                            const std::string &ws, int depth)
{
    if(node == NULL) return;
   
    std::string side;
    if(node->getParent() != NULL)
    {
        if(node->getParent()->getLeftChild() == node) side = "left";
        else if(node->getParent()->getRightChild() == node) side = "right";
        else side = "ERROR - Unknown Parent";
    }
    else side = "root";

    out << ws;
    if(depth > -1) out << depth++ << ".";
    out << node->getData();
    out <<"("<< (!node->getColor()?'r':'b') << ")";
    if(depth > -1) out <<"["<< side << "]";
    out << '\n';
    
    std::string new_ws = ws + "\t";

    this->printTree(out, node->getLeftChild(), new_ws, depth);
    this->printTree(out, node->getRightChild(), new_ws, depth);

    return;
}

