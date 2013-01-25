#include <string>
#include <pagebst.hpp>
#include "webpage.hpp"

//!  binary search tree for webpages

//!  No-arg constructor.  Initializes an empty BST
pagebst::pagebst()
{
    bstsize = 0;
}


//!  Copy constructor.  Makes a complete copy of its argument
pagebst::pagebst(const pagebst & other)
{
    if(this!=&other)
    {
        this->CopyBST(other);
    }
}


//!  Destructor
pagebst::~pagebst()
{
}


//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
pagebst& pagebst::operator =(const pagebst & other)
{
    if(this!=&other)
    {
        this->CopyBST(other);
    }
    return *this;
}


//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for BST clients that need to traverse the tree.)
pageNode * pagebst::GetRoot()const
{
}


//!  @return true if the BST is empty, or false if the BST is not empty
bool pagebst::IsEmpty() const
{
    
}


//!  Removes all values from the BST
void pagebst::Clear()
{
}


//!  @return the number of values in the BST
int pagebst::GetSize() const
{
    
}


//!  Inserts value v into the BST
//!  
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
pageNode * pagebst::Insert(const pageNode & val)
{
    return NULL;
}


//!  Searches the tree for value v
//!  
//!  @param v The new value being searched for
//!
//!  @return a pointer to the node containing v, or NULL if v is not in the tree
pageNode * pagebst::Find(const std::string & val) const
{
    return NULL;
}


//!  Removes value v from the tree
//!  
//!  @param v The value being removed from the tree
//!
//!  @return true if v was removed from the tree, or false if v was not in the tree
//bool Remove(const std::string & v);

void pagebst::CopyBST(const pagebst & other)
{
}

pageNode * pagebst::HelpFind(pageNode * treenode, const std::string & val) const
{
    return treenode;
}

void pagebst::HelpClear(pageNode * bstn)
{
}

pageNode * pagebst::HelpInsert(pageNode * curnode, const pageNode & val)
{
    return curnode;
}

//pagebst class implemented
