/* 
   Ethan D. Estrada
   ID: 411688971
   CS 235 Fall 2012 Midterm 1
*/

#ifndef _POLYMAN_H_
#define _POLYMAN_H_

#include "PolynomialManagerInterface.h"
#include "PolynomialListInterface.h"
#include "PolyList.h"
#include <string>

class PolyMan : public PolynomialManagerInterface
{
private:
    PolyList listOne, listTwo;

public:
	PolyMan();
	virtual ~PolyMan();

	/*
	 * addLists()
	 * This function goes through the process of adding your two list's together and returning the resulting list.
	 * Like terms should be added together correctly, creating one Node for the final list.
	 * If both of the lists are empty, return an empty list. This list must be sorted in correct polynomial order by degree.
	 * i.e.
	 * (2x^4)->(4x^2)->(3x^1)->(11x^0), not (2x^4)->(3x^1)->(11x^0)->(4x^2) or anything else.
	 */
	virtual PolynomialListInterface * addLists();

	/*
	 * subtractLists()
	 * This function goes through the process of subtracting your list two from your list one and returning the resulting list.
	 * Like terms should be subtracted correctly, creating one Node for the final list. If a resulting coefficient is 0, that node should be removed.
	 * If both of the lists are empty, return an empty list. This list must be sorted in correct polynomial order by degree.
	 * i.e.
	 * (2x^4)->(4x^2)->(3x^1)->(11x^0), not (2x^4)->(3x^1)->(11x^0)->(4x^2) or anything else.
	 */
	virtual PolynomialListInterface * subtractLists();

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
	virtual void fillListOne(std::string term);

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
	virtual void fillListTwo(std::string term);

	/*
	 * clearListOne()
	 * This function should empty your first list entirely.
	 */
	virtual void clearListOne();

	/*
	 * clearListTwo()
	 * This function should empty your second list entirely.
	 */
	virtual void clearListTwo();

	/*
	 * getListOne()
	 * Returns a pointer to the first list.
	 */
	virtual PolynomialListInterface * getListOne();

	/*
	 * getListTwo()
	 * Returns a pointer to the second list.
	 */
	virtual PolynomialListInterface * getListTwo();
};

#endif //_POLYMAN_H_
