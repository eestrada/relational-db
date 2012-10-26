#include <iostream>
#include <string>
#include "PolyList.h"
#include "PolyMan.h"

using std::cout;
using std::endl;
using std::cin;

int main(void)
{
    PolyMan pmtest;


    pmtest.fillListOne("3x^7");
    pmtest.fillListOne("2x^2");
    pmtest.fillListTwo("2x^9");
    PolynomialListInterface * mine = pmtest.addLists();

    mine->printList();
    pmtest.subtractLists();
//    pmtest.clearListOne();

    PolynomialListInterface * tmp = pmtest.getListTwo();

    std::string atstr = tmp->at(9);

    pmtest.fillListOne("fjdasio;");

    return 0;
}

