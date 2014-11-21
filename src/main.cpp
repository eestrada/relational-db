#include "Driver.h"
#include <ctime>
#include <iostream>

int main(int argc, char **argv)
{
	std::clock_t t;
	t = std::clock();
    auto retval = Driver::interpret(argc, argv);
    t = std::clock() - t;
    std::cout << "Took me " << t << " clicks (around " << float(t)/CLOCKS_PER_SEC << " seconds).\n";
    return retval;
}

