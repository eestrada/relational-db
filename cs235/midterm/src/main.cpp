#include "deque.h"
#include "main.h"
#include <iostream>

int main(int argc, char **argv)
{
    bool running = true;
    std::cin.exceptions( std::istream::failbit | std::istream::badbit );

    while(running)
    {
        std::cerr << "Pick your poison:\n";
        std::cerr << "[0] Quit\n";
        std::cerr << "[1] Test all\n";
        std::cerr << "[2] Test deque\n";
        std::cerr << "[3] Test queue\n";
        std::cerr << "[4] Test stack\n";
        std::cerr << "[5] Test ir_deque\n";
        std::cerr << "[6] Test or_deque\n";
        std::cerr << "Input: " << std::flush;

        int input;

        try
        {
            std::cin >> input;
        }
        catch(std::istream::failure &e)
        {
            std::cerr << e.what() << std::endl;
            break;
        }

        switch(input)
        {
            case 0: running = false; break;
            case 1: std::cerr << "Option 1 chosen.\n"; break;
            case 2: std::cerr << "Option 2 chosen.\n"; break;
            case 3: std::cerr << "Option 3 chosen.\n"; break;
            case 4: std::cerr << "Option 4 chosen.\n"; break;
            case 5: std::cerr << "Option 5 chosen.\n"; break;
            case 6: std::cerr << "Option 6 chosen.\n"; break;
            default: std::cerr << "Invalid option given.\n"; break;
        }


    }

    std::cerr << "End of program." << std::endl;
}

