#if !defined(_AVL_HPP_)
#define _AVL_HPP_

#include "AVLInterface.h"
#include "Node.hpp"
#include <string>

namespace ede
{

class AVL : public AVLInterface
{
private:
    Node *root, *head, *tail;

	virtual bool addNode(Node *current, int data);
	virtual bool removeNode(Node *current, int data);

public:
	AVL();
	virtual ~AVL();

    virtual std::string recurse();

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	virtual NodeInterface * getRootNode();

	/*
	 * Attempts to add the given int to the AVL tree
	 * Rebalances the tree if data is successfully added
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	virtual bool add(int data);

	/*
	 * Attempts to remove the given int from the AVL tree
	 * Rebalances the tree if data is successfully removed
	 *
	 * @return true if successfully removed
	 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
	 */
	virtual bool remove(int data);

	/*
	 * ROTATIONS:
	 * 			LEFT
	 *
	 * 				IDENTIFY NODES TO ROTATE
	 *
	 * 				ROT.RIGHT=CUR.LEFT
	 * 				CUR.LEFT=ROT
	 * 				CUR=ROT
	 *
	 *
	 *
	 *
	 * 			RIGHT
	 *
	 *
	 *
	 */
};

}
#endif // define _AVL_HPP_

