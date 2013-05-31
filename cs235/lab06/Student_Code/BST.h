#ifndef _BST_HPP_
#define _BST_HPP_

#include "NodeInterface.h"
#include "Node.h"
#include "BSTInterface.h"

namespace ede
{

class BST : public BSTInterface
{
private:
    Node *root;

    virtual bool addNode(Node *current, int val);
    
    virtual bool removeNode(Node *current, int val);
public:
	BST() : root(NULL){}
	
    virtual ~BST()
    {
        delete(root);
    }

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	virtual NodeInterface * getRootNode();

	/*
	 * Attempts to add the given int to the BST tree
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	virtual bool add(int data);

	/*
	 * Attempts to remove the given int from the BST tree
	 *
	 * @return true if successfully removed
	 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
	 */
	virtual bool remove(int data);
};

}

#endif // defined _BST_HPP_

