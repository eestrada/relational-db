#include <iostream>
#include <string>
#include "LinkedList.hpp"

using namespace std;


void LinkedList::printMe()
{
    cout << "Printing List contents.\n" << endl;

    llnode *tmp = this->head;
    for(int i = 0; i < this->mysize; i++)
    {
        cout << "My size is: " << this->mysize << endl;

        cout << i << ": " << tmp->data << endl;
        tmp = tmp->next;
    }

}


/*
 * Returns a pointer to the address of the node with value "value".
 *
 * Returns a null pointer if the value does not exist.
 *
 * */


void LinkedList::findNode(int value, llnode *parent, llnode *child)
{
    llnode *tmpA = NULL, *tmpB = this->head;

    for(int i = 0; i < this->mysize; i++)
    {
        cout << "tmpB is: " << tmpB << endl;
        if(tmpB->data == value)
        {
            break;
        }

        tmpA = tmpB;
        tmpB = tmpB->next;
    }

    parent = tmpA;
    child = tmpB;

    //If the value doesn't exist then child value should be NULL
    //since the "next" variable of the tail node is always NULL.

    return;
}

llnode* LinkedList::findNode(int index)
{
    if(index <= this->mysize && index <= 0)
    {
        llnode *tmp = this->head;

        for(int i = 0; i < this->mysize; i++)
        {
           if(i == index)
           {
               return tmp;
           }
           else
           {
               tmp = tmp->next;
           }
        }
    }

    // If we are here, that means the index is out of range.
    return NULL;
}
/*
insertHead

A node with the given value should be inserted at the beginning of the list.

Only non-negative values should be added to the list. Do not allow
duplicate values in the list.
*/
void LinkedList::insertHead(int value)
{
    llnode *tmpA, *tmpB;

    this->findNode(value, tmpA, tmpB);

    if(value >= 0 && tmpB == NULL)
    {
        llnode * tmp = new llnode(value, head);
        head = tmp;

        if(tail == NULL) tail = tmp;
        
        this->mysize += 1;

        this->printMe();


    }
}

/*
insertTail

A node with the given value should be inserted at the end of the list.

Only non-negative values should be added to the list. Do not allow
duplicate values in the list.
*/
void LinkedList::insertTail(int value)
{
    llnode *tmpA, *tmpB;

    this->findNode(value, tmpA, tmpB);

    if(value >= 0 && tmpB == NULL)
    {
        llnode *tmp = new llnode(value, NULL);

        if(tail == NULL)
        {
            tail = tmp;
            head = tmp;


        }
        else
        {
            tail->next = tmp;
            tail = tmp;
        }
        
        this->mysize += 1;

    }
}

/*
insertAfter

A node with the given value should be inserted immediately after the
node whose value is equal to insertionNode.

A node should only be added if the node whose value is equal to
insertionNode is in the list. Only non-negative values should be
added to the list. Do not allow duplicate values in the list.
*/
void LinkedList::insertAfter(int value, int insertionNode)
{
    llnode *nodeA, *nodeB;

    this->findNode(insertionNode, nodeA, nodeB);

    if(nodeB != NULL)
    {
        nodeA = new llnode(value, nodeB->next);
        nodeB->next = nodeA;

        this->mysize += 1;
    }
}

/*
remove

The node with the given value should be removed from the list.

The list may or may not include a node with the given value.
*/
void LinkedList::remove(int value)
{
    llnode *tmpA = NULL, *tmpB = NULL;

    this->findNode(value, tmpA, tmpB);

    if(tmpB != NULL) // If the node has a real address then we can remove it.
    {
        // If our node is the head then we need to be sure to change what
        // "head" points to.
        if(tmpB == this->head)
        {
            this->head = tmpB->next;

            //If head is now pointing to NULL, then so must tail.
            if(this->head == NULL)
            {
                this->tail = NULL;
            }
        }
        else
        {
            // Since we know our node isn't NULL and isn't head, then we know it
            // has a parent. Be sure to reassign the parent's "next" pointer.
            tmpA->next = tmpB->next;
        }

        // After all our safety checks, delete our node (the final step in
        // removal).
        delete(tmpB);

        this->mysize -= 1;
    }
}

/*
clear

Remove all nodes from the list.
*/
void LinkedList::clear()
{
    llnode *tmpA = this->head, *tmpB = NULL;
    for(int i = 0; i < this->mysize ; i++)
    {
        tmpB = tmpA->next;

        delete(tmpA);

        tmpA = tmpB;
    }

    this -> mysize = 0;
}

/*
at

Returns the value of the node at the given index. The list begins at
index 0.

If the given index is out of range of the list, return -1;
*/
int LinkedList::at(int index)
{
    llnode *inode = this->findNode(index);

    if(inode != NULL)
        {return inode->data;}

    return -1;
}

/*
size

Returns the number of nodes in the list.
*/
int LinkedList::size()
{
    return this -> mysize;
}

