#include "Factory.h"
#include "AVL.hpp"
#include <iostream>

int main(void)
{
    std::cout << "Testing lab10." << std::endl;
    Factory factest;

    ede::AVL &tmpavl = *(static_cast<ede::AVL*>(factest.getAVL()));

    std::cout << "AVL's root address is: " << tmpavl.getRootNode() << std::endl;

    tmpavl.add(10);
    std::cout << "AVL's root address is: " << tmpavl.getRootNode() << std::endl;
    std::cout << "AVL's root value is: " << tmpavl.getRootNode()->getData() << std::endl;

    std::cout << "AVL's tree is: " << tmpavl.recurse() << std::endl;

    delete(&tmpavl);
    return 0;
}

