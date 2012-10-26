/* 
   Ethan D. Estrada
   ID: 411688971
   CS 235 Fall 2012 Midterm 1
*/

#include "PolyMan.h"
#include <string>
#include <iostream>
#include "nullstream.hpp"

ede::nostream null_pmout;
// When I am done debugging, simply swap null_pmout for cout. Then all
// output statements will no longer print anything.
std::ostream &pmout = null_pmout; 

PolyMan::PolyMan(){}
PolyMan::~PolyMan(){}

/*
 * addLists()
 * This function goes through the process of adding your two list's together and returning the resulting list.
 * Like terms should be added together correctly, creating one Node for the final list.
 * If both of the lists are empty, return an empty list. This list must be sorted in correct polynomial order by degree.
 * i.e.
 * (2x^4)->(4x^2)->(3x^1)->(11x^0), not (2x^4)->(3x^1)->(11x^0)->(4x^2) or anything else.
 */
PolynomialListInterface * PolyMan::addLists()
{
    PolyList * leak = new PolyList();
    pmout << "Add lists and returning NULL." << std::endl;

    bool added;

    for( int i = 0; i < listOne.size(); ++i )
    {
        added = false;
        PolyNode cur1 = listOne.nodeAt(i);
        for (int j = 0; j < listTwo.size(); ++j )
        {
            PolyNode cur2 = listTwo.nodeAt(j);
            if ( cur1.exponent == cur2.exponent )
            {
                added = true;

                leak->insert( (cur1 + cur2).pstr );
            }
        }

        if (!added)
        {
            leak->insert(listOne.at(i));
        }
    }

    for (int i = 0; i < listTwo.size(); ++i)
    {
        bool exists = false;

        PolyNode cur1 = listTwo.nodeAt(i);
        for (int j = 0; j < leak->size(); ++j)
        {
            PolyNode cur2 = leak->nodeAt(j);
            if(cur1.exponent == cur2.exponent)
            {
                exists = true;
                break;
            }
        }

        if(!exists)
        {
            leak->insert(cur1.pstr);
        }
    }

    this->listOne.sort();
    this->listTwo.sort();

    leak->printList();

    return leak;
}

/*
 * subtractLists()
 * This function goes through the process of subtracting your list two from your list one and returning the resulting list.
 * Like terms should be subtracted correctly, creating one Node for the final list. If a resulting coefficient is 0, that node should be removed.
 * If both of the lists are empty, return an empty list. This list must be sorted in correct polynomial order by degree.
 * i.e.
 * (2x^4)->(4x^2)->(3x^1)->(11x^0), not (2x^4)->(3x^1)->(11x^0)->(4x^2) or anything else.
 */
PolynomialListInterface * PolyMan::subtractLists()
{


    PolyList * leak = new PolyList();
    pmout << "Add lists and returning NULL." << std::endl;

    bool added;

    for( int i = 0; i < listOne.size(); ++i )
    {
        added = false;
        PolyNode cur1 = listOne.nodeAt(i);
        for (int j = 0; j < listTwo.size(); ++j )
        {
            PolyNode cur2 = listTwo.nodeAt(j);
            if ( cur1.exponent == cur2.exponent )
            {
                added = true;

                leak->insert( (cur1 - cur2).pstr );
            }
        }

        if (!added)
        {
            leak->insert(listOne.at(i));
        }
    }

    for (int i = 0; i < listTwo.size(); ++i)
    {
        bool exists = false;

        PolyNode cur1 = listTwo.nodeAt(i);
        for (int j = 0; j < leak->size(); ++j)
        {
            PolyNode cur2 = leak->nodeAt(j);
            if(cur1.exponent == cur2.exponent)
            {
                exists = true;
                break;
            }
        }

        if(!exists)
        {
            leak->insert(cur1.pstr);
        }
    }

    this->listOne.sort();
    this->listTwo.sort();

    leak->printList();

    return leak;
}

/*
 * fillListOne(std::string term)
 * This adds a single term at a time.
 * This function will be called many times while your first list is being filled.
 * You should add the new term at the appropriate spot in the list
 * which may involve adding it to an existing polynomial list, the list should be ordered by degrees.
 * All segments will have at least a variable and an exponent, however the Coefficient may be an implied 1.
 * i.e. x^6 is valid, but 2x is not.
 * If the term is not valid, it should not be added to the list.
 *
 */
void PolyMan::fillListOne(std::string term)
{
    pmout << "Attempting to fill list one." << std::endl;
    this->listOne.insert(term); 
}

/*
 * fillListTwo(std::string term)
 * This adds a single term at a time.
 * This function will be called many times while your second list is being filled.
 * You should add the new term at the appropriate spot in the list
 * which may involve adding it to an existing polynomial list, the list should be ordered by degrees.
 * All segments will have at least a variable and an exponent, however the Coefficient may be an implied 1.
 * i.e. x^6 is valid, but 2x is not.
 * If the term is not valid, it should not be added to the list.
 */
void PolyMan::fillListTwo(std::string term)
{
    pmout << "Attempting to fill list two." << std::endl;
    this->listTwo.insert(term); 
}

/*
 * clearListOne()
 * This function should empty your first list entirely.
 */
void PolyMan::clearListOne()
{
    pmout << "Trying to clear list one." << endl;
    this->listOne.erase();
}

/*
 * clearListTwo()
 * This function should empty your second list entirely.
 */
void PolyMan::clearListTwo()
{
    pmout << "Trying to clear list two." << endl;
    this->listTwo.erase();
}

/*
 * getListOne()
 * Returns a pointer to the first list.
 */
PolynomialListInterface * PolyMan::getListOne()
{
    pmout << "Currently returning address of list one." << std::endl;
    return &(this->listOne);
}

/*
 * getListTwo()
 * Returns a pointer to the second list.
 */
PolynomialListInterface * PolyMan::getListTwo()
{
    pmout << "Currently returning address of list two." << std::endl;
    return &(this->listTwo);
}

