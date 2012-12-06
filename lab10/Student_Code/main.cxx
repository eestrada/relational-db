#include "Factory.h"
#include "AVL.hpp"
#include <iostream>

int main(void)
{
    std::cout << "Testing lab10." << std::endl;
    Factory factest;

    ede::AVL &tmpavl = *(static_cast<ede::AVL*>(factest.getAVL()));

    tmpavl.add(5);
    std::cout << "Added 5" << std::endl;
    tmpavl.add(10);
    std::cout << "Added 10" << std::endl;
    tmpavl.add(3);
    std::cout << "Added 3" << std::endl;
    tmpavl.add(2);
    std::cout << "Added 2" << std::endl;
    tmpavl.add(1);
    std::cout << "Added 1" << std::endl;
    tmpavl.add(6);
    tmpavl.add(-5);

    std::cout << "AVL's tree is:\n\n" << tmpavl.recurse() << std::endl;

    delete(&tmpavl);
    return 0;
}

