#ifndef PAGELLIST_HPP
#define PAGELLIST_HPP

#include <string>
#include "webpage.hpp"

//!  pageNode implements a binary search tree node
class pageNode
{
    friend class pagebst;   //!< BST can access private members of pageNode

	public:

		//!  Constructor
		pageNode(const webpage & v) :
		  value(v), left(NULL), right(NULL)
		{
		}

		//! Copy Constructor
		pageNode(const pageNode & other) :
		  value(other.value),left(other.left),right(other.right)
		{
		}


		//!  Read-only public methods for use by clients of the BST class
		const std::string & GetValue()
		{
            return value.getURL();
		}


		pageNode * GetLeft()const
		{
            return left;
		}


		pageNode * GetRight()const
		{
            return right;
		}

		//! Assignment operator 
		pageNode & operator=(const pageNode & other)
		{
			if(this!=&other)
			{
				value=other.value;
				left=other.left;
				right=other.right;
			}
			
			return *this;
		}

	private:
		webpage value;  //!< value stored in the node
		pageNode * left;     //!< pointer to the node's left child
		pageNode * right;    //!< pointer to the node's right child
};


//!  binary search tree for webpages
class pagebst 
{

	public:
	
		//!  No-arg constructor.  Initializes an empty BST
		pagebst();


		//!  Copy constructor.  Makes a complete copy of its argument
		pagebst(const pagebst & other);


		//!  Destructor
		~pagebst();


		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		pagebst& operator =(const pagebst & other);


		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BST clients that need to traverse the tree.)
		pageNode * GetRoot()const;


		//!  @return true if the BST is empty, or false if the BST is not empty
		bool IsEmpty() const;


		//!  Removes all values from the BST
		void Clear();


		//!  @return the number of values in the BST
		int GetSize() const;


		//!  Inserts value v into the BST
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		pageNode * Insert(const pageNode & val);


		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		pageNode * Find(const std::string & val) const;


		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const std::string & v);

	private:

		pageNode * rootnode;
		int bstsize;

		void CopyBST(const pagebst & other);

		pageNode * HelpFind(pageNode * treenode, const std::string & val) const;

		void HelpClear(pageNode * bstn);

		pageNode * HelpInsert(pageNode * curnode, const pageNode & val);
};

#endif //PAGELLIST_HPP defined
