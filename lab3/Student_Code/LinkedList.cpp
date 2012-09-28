#include <iostream>
#include <string>
#include "LinkedList.hpp"

using namespace std;


void LinkedList::printMe()
{
    cout << "head is: " << head->data << endl;
    cout << "tail is: " << tail->data << endl;   
}


/*
 * Returns a pointer to the address of the node with value "value".
 *
 * Returns a value of -1 if the value does not exist.
 *
 * */


llnode* LinkedList::findNode(int value)
{
    if(index >= this->mysize)
    {
        llnode* tmp = this->head;
        for(int i = 0; i < this->mysize; i++)
        {
            if(i == index)
            {
                return tmp;
            }

            if(tmp == NULL)
            {
                break;
            }

            tmp = tmp->next;
        }
    }
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
    llnode * tmp = new llnode(value, head);
    head = tmp;

    if(tail == NULL) tail = tmp;

    this->printMe();
}

/*
insertTail

A node with the given value should be inserted at the end of the list.

Only non-negative values should be added to the list. Do not allow
duplicate values in the list.
*/
void LinkedList::insertTail(int value)
{
    if(value >= 0)
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
    }

    this->printMe();
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
}

/*
remove

The node with the given value should be removed from the list.

The list may or may not include a node with the given value.
*/
void LinkedList::remove(int value)
{
    llnode *tmpA, *tmpB;

    if(value == 0)
    {
        tmpA = this->head;
        this->head = this->head->next;
        delete(tmpA);
        this -> mysize -= 1;
    }
    else if(value > 0 && value < this->mysize)
    {
        tmpA = this -> findNode(static_cast<unsigned int>(value-1));
        tmpB = tmpA->next;
        tmpA->next = tmpB->next;
        delete(tmpB);
        this -> mysize -= 1;
    }

}

/*
clear

Remove all nodes from the list.
*/
void LinkedList::clear()
{
    for(int i = this->mysize - 1; i >= 0 ; i--)
    {
        this->remove(i);
    }

//    this -> mysize = 0;

    this->printMe();
}

/*
at

Returns the value of the node at the given index. The list begins at
index 0.

If the given index is out of range of the list, return -1;
*/
int LinkedList::at(int index)
{
    llnode *tmp = this->findNode(index);
    return tmp->data;
}

/*
size

Returns the number of nodes in the list.
*/
int LinkedList::size()
{
    return this -> mysize;
}

