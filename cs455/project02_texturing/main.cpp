/* Include my headers */

#include "main.hpp"

int main(int argc, char **argv)
{
    int retval = 0;

    try
    {
        retval = ede::main(argc, argv);
    }
    catch(system_exit &e)
    {
        if (e.code() != 0)
        {
            std::cerr << "Abnormal exit for following reason" << e.what() << std::endl;
            retval = e.code();
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "There was an unexpected exit due to the following exception: ";
        std::cerr << e.what() << std::endl;
        retval = -1;
    }

    return retval;

}
