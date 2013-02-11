#include "Parser.h"
#include "DatalogProgram.h"
#include "Domain.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

const string dash("-");

int main(int argc, char* argv[])
{
    
    if(argc == 1)
    {
        clog << "Error! Not enough arguments specified.\n";
        clog << "You must specify either a file or the special option '-'. ";
        clog << "Using the option '-' will read from standard input.\n";
        return -1;
    }

    Parser *p;

    if(dash == argv[1])
    {
        p = new Parser(cin);
    }
    else
    {
        p = new Parser(argv[1]);
    }

    Parser &parse = *p;

    cout << parse;//.toString();

    delete p;

    return 0;
}

