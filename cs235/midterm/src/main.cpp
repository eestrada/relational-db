#include "deque.h"
#include "main.h"
#include <climits>
#include <iostream>

int main(int argc, char **argv)
{
    bool running = true;
    int retval = 0;
    std::cin.exceptions( std::istream::failbit | std::istream::badbit );

    while(running)
    {
        std::cerr << "Pick your poison:\n";
        std::cerr << "[0] Quit\n";
        std::cerr << "[1] Test all\n";
        std::cerr << "[2] Test stack\n";
        std::cerr << "[3] Test queue\n";
        std::cerr << "[4] Test deque\n";
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
            //std::cerr << "Improper input resulted in the following error: ";
            //std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            input = -1;
        }

        try
        {
            switch(input)
            {
                case 0: running = false; break;
                case 1: test_all(); break;
                case 2: test_stack(); break;
                case 3: test_queue(); break;
                case 4: test_deque(); break;
                case 5: test_ir_deque(); break;
                case 6: test_or_deque(); break;
                default: std::cerr << "Invalid option given.\n";
            }
        }
        catch(std::exception &e)
        {
            std::cerr << "Test failed for following reason: " << e.what() << "\n";
        }
    }

    //std::cerr << "End of program." << std::endl;

    return retval;
}

