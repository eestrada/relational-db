#include <iostream>
#include <string>
#include "parser.hpp"
#include "webpage.hpp"
#include "pagebst.hpp"
#include "word.hpp"
#include "xmlgen.hpp"

int main(int argc, char * argv[])
{
    std::string tmp(argv[1]);
    std::cout << tmp << std::endl;
    
    webpage tmppage(tmp);
    pagebst * bstptr = new pagebst();
    bstptr->Insert(tmppage);
    
    return 0;
}
