#include <iostream>
#include <string>
#include "LinkedList.hpp"

using namespace std;


void LinkedList::printMe()
{
    cout << "Printing List contents.\n" << endl;

    if (this->head != NULL)
    {
        llnode *tmp = this->head;

        cout << "My size is: " << this->mysize << endl;

        for(int i = 0; i < this->mysize; i++)
        {

            cout << i << ": " << tmp->data << endl;
            tmp = tmp->next;
        }
    }
    else
    {
        cout << "Head is NULL. Can't print list." << endl;
    }

}
bool LinkedList::valExists(int value)
{
    llnode *tmp = this->head;

    bool valueExists = false;

    while(tmp != NULL)
    {
        if(tmp->data == value)
        {
            valueExists = true;
            break;
        }

        tmp = tmp->next;
    }

    return valueExists;

}


/*
insertHead

A node with the given value should be inserted at the beginning of the list.

Only non-negative values should be added to the list. Do not allow
duplicate values in the list.
*/
void LinkedList::insertHead(int value)
{
    if(value >= 0 && this->valExists(value) == false)
    {
        llnode * tmp = new llnode(value, head);
        head = tmp;

        if(tail == NULL) tail = tmp;
        
        this->mysize += 1;

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
    if(value >= 0 && this->valExists(value) == false)
    {
        llnode *tmp = new llnode(value, NULL);

        if(tail == NULL)
        {
            tail = tmp;
            head = tmp;
        }
        else
        {
            // Point the current tail node at the new tail node.
            tail->next = tmp;

            // Make the new node the current tail.
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
    // Only accept valid values for insertion.
    if(value >= 0 && this->valExists(value) == false && this->valExists(insertionNode) == true)
    {
        llnode *tmp = this->head;

        // If tmp = NULL then we have hit the end of the list.
        while(tmp != NULL)
        {
            // Run the insertion code if this node has the insertion value.
            if(tmp->data == insertionNode)
            {
                llnode *newNode = new llnode(value, tmp->next);
                tmp->next = newNode;
                
                // If we are inserting after the tail, be sure to update tail.
                if(tmp == this->tail)
                    {this->tail = newNode;}

                this->mysize += 1;

                // If we have inserted then we should break the loop.
                break;
            }

            // Iterate to the next node
            tmp = tmp->next;
        }
    }
}

/*
remove

The node with the given value should be removed from the list.

The list may or may not include a node with the given value.
*/
void LinkedList::remove(int value)
{
    // Only run code if this value exists
    if(this->valExists(value) == true)
    {
        llnode *tmp = this->head;

        // Separate code branch for if head contains the value.
        if(tmp->data == value)
        {
            this->head = this->head->next;
            if(this->tail == tmp)
                {this->tail = this->head;}

            delete tmp;
            this->mysize -= 1;
        }
        else
        {
            while(tmp != NULL) 
            {
                llnode *nextNode = tmp->next;

                // If we have found the value, delete the node and break the 
                // loop.
                if(nextNode->data == value)
                {
                    tmp->next = nextNode->next;

                    if(nextNode == this->tail)
                    {
                        this->tail = tmp;
                    }

                    delete nextNode;
                    this->mysize -= 1;
                    break;
                }

                // If we haven't found the value, move onto the next node.
                tmp = nextNode;
            }
        }
    }
}

/*
clear

Remove all nodes from the list.
*/
void LinkedList::clear()
{
    llnode *tmpA = this->head, *tmpB;
  
    // Delete from head to tail. Stop when we hit NULL.
    while(tmpA != NULL)
    {
        tmpB = tmpA->next;

        delete(tmpA);

        tmpA = tmpB;
    }

    // Reset head and tail to null.
    this->head = NULL;
    this->tail = NULL;

    // Reset size to zero.
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
    int retval = -1, i = 0;

    llnode *tmp = this->head;
    while(tmp != NULL)
    {
        // If we have iterated forward to the index, then return the current
        // node's data.
        if(i == index)
        {
            retval = tmp->data;
            break;
        }

        // Didn't find it so increase current index and look to next node.
        ++i;
        tmp = tmp->next;

    }

    // Return value. If the index doesn't exist, then the initial value of -1
    // will be returned.
    return retval;
}

/*
size

Returns the number of nodes in the list.
*/
int LinkedList::size()
{
    return this -> mysize;
}

