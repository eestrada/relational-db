#include <iostream>
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
    pmtest.addLists();
    pmtest.subtractLists();
    pmtest.clearListOne();

    pmtest.fillListOne("fjdasio;");

//    cout << "This is a test." << endl;
    return 0;
}

