/* 
   Ethan D. Estrada
   ID: 411688971
   CS 235 Fall 2012 Midterm 1
*/

#include "PolyList.h"
#include <string>
#include <iostream>
#include "nullstream.hpp"

ede::nostream null_plout;
std::ostream &plout = std::cout;


/*
 * You must create a Node class that will hold each polynomial segment and will be used to create the
 * links in your PolynomialList.
 * Your Node will likely have 3 private variables in addition to a Node * next you may have.
 * These 3 variables will be for the Coefficient, the Variable, and the Exponent respectively.
 * i.e. 2x^7
 * 		Coefficient = 2
 * 		Variable = x
 * 		Exponent = 7
 */
PolyList::PolyList(void){}
PolyList::~PolyList(void){}


bool isValid(std::string term)
{
    char var;
    int coefficient, exponent;
    std::istringstream in(term);

    char c = in.peek();

    // Check to see if we start with a number
    if((c > '0') && (c<= '9'))
        in >> coefficient;
    else
        coefficient = 1;

    in >> var;
    in.ignore(1); // ignore '^' character
    in >> exponent;

    return !in.fail(); // If string was poorly formatted this will fail.
}

/*
    insert

    A node with the given term should be inserted at the appropriate spot in the list.
    A term can be accepted only with Coefficient value > 0, and exponent value non-negative.
    If the term is invalid, do not add it to the list.
    i.e. If the given term segment is 3x^5 and your list contains 2x^8, x^4, 11x^2
        the node should be added after 2x^8. Your updated list should look like 2x^8, 3x^5, x^4, 11x^2.

 */
void PolyList::insert(std::string term)
{
    if(isValid(term)) // Only insert if the formatting is valid.
    {
        plout << "Insertion accepted!\n";

        PolyNode tmpNode(term);

        this->push_front(tmpNode);

        this->sort();
    }
    else
    {
        plout << "Insertion FAILED! \"" << term << "\" is not a properly formatted string.\n";
    }

    
    plout << this->printList() << std::endl;
    
}

/*
    clear

    Remove all nodes from the list.
 */
void PolyList::clear()
{
    ede::list<PolyNode>::erase();
}

/*
    at

    Returns the polynomial of the node at the given index. The list begins at
    index 0.

    If the given index is out of range of the list, return "invalid";
 */
std::string PolyList::at(int index)
{
    return std::string();
}

/*
    size

    Returns the number of nodes in the list.
 */
int PolyList::size()
{
    return ede::list<PolyNode>::size();
}

/*
 * This function should string together all of the nodes and print out the entire polynomial separated with '+' signs.
 * If an exponent of 0 exists however, you should print only the Coefficient.
 * i.e. list of Nodes = (2x^4)->(4x^2)->(3x^1)->(11x^0)
 * 		printList() = return "2 x ^ 4 + 4 x ^ 2 + 3 x + 11";
 */
std::string PolyList::printList()
{
    std::ostringstream retstr;

    llnode *current = this->head;

    //for (int i = 0; i < this->size(); ++i)
    while( current != NULL )
    {
        if(current != this->head)
            retstr << " + ";

        retstr << current->data.pstr;

        current = current->next;
    }

    return retstr.str();
}

void PolyList::sort()
{

    llnode *current = this->head, *tmp;

    bool stop = false;

    while(!stop && this->size() > 0)
    {
        // We only set this back to false if we swap values on this iteration.
        stop = true;

        while( current != NULL )
        {
            tmp = current->next;

            if(tmp != NULL && current->data < tmp->data) // Items need to be swapped
            {
                tmp->prev = current->prev;
                current->next = tmp->next;
                tmp->next = current;
                current->prev = tmp;

                this->head = ( this->head == current ) ? tmp : this->head;

                stop = false;
            }
            else
            {
                current = current->next;
            }
        }
    }
}
