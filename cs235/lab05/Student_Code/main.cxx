#include <iostream>
#include "Station.hpp"

using namespace ede;

int main(void)
{
    deque<int> test;
    
    test.push_back(5);

    std::cout << test.back() << std::endl;

    return 0;
}
