#pragma once

#include <string>
#include "RedBlackNodeInterface.h"

//using namespace std;
//using namespace ::;
//using namespace ;

class RedBlackNode;
typedef RedBlackNode rbn;

enum color{ RED = 0, BLACK = 1 };

class RedBlackNode : public RedBlackNodeInterface
{
friend class RedBlackTree;
private:
    std::string data;
    color clr;
    rbn *parent, *left, *right;
    
	/*
	 * Set color of this node.
	 *
	 * @param c Color to set as the node color.
	 */
    void setColor(color c){clr = c;}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return The left child of this node or null if it doesn't have one.
	 */
    rbn* getParent(){return parent;}
	
	/*
	 * Set the parent of this node to "p".
	 *
	 * @param p Pointer to set as the parent.
	 */
    void setParent(rbn *p){parent = p;}

	/*
	 * Set the left child of this node to "l".
	 *
	 * @param l Pointer to set as the new left child.
	 */
    void setLeftChild(rbn *l){left = l;}
	
	/*
	 * Set the right child of this node to "r".
	 *
	 * @param r Pointer to set as the new left child.
	 */
    void setRightChild(rbn *r){right = r;}

public:
	RedBlackNode(std::string val="", color c=RED, rbn *p=NULL, rbn *l=NULL, rbn *r=NULL)
        : data(val), clr(c), parent(p), left(l), right(r) {}
	virtual ~RedBlackNode()
    {
        delete(left);
        delete(right);
    }

	/*
	 * Returns the word that is stored in this node
	 *
	 * @return The word that is stored in this node.
	 */
	virtual std::string getWord(){return data;}

	/*
	 * Returns the color of the node. A red node should return 0
	 * and a black node should return 1.
	 *
	 * @return The color of the node
	 */
	virtual int getColor(){return clr;}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return The left child of this node or null if it doesn't have one.
	 */
	virtual RedBlackNode * getLeftChild(){return left;}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return The right child of this node or null if it doesn't have one.
	 */
	virtual RedBlackNode * getRightChild(){return right;}

};
