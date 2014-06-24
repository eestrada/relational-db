#include <iostream>
#include "Lexer.hpp"

int main(int argc, char **argv)
{
    using namespace std;

    cerr << "Dummy code for a place holder." << endl;

    Lex::Lexer l(std::cin);

    l.next();
    
    return EXIT_SUCCESS;
}
