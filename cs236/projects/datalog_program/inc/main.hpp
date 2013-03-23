#ifndef MAIN_H
#define MAIN_H

#include "Parser.hpp"
#include "DatalogProgram.hpp"
#include "Domain.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

inline int parseArgs(int argc, char *argv[], std::ostream &out, std::ostream &err)
{
    if(argc == 1)
    {
        err << "Error! Not enough arguments specified.\n";
        err << "You must specify either a file or the special option '-'. ";
        err << "Using the option '-' will read from standard input.\n";
        err.flush();

        return -1;
    }

    Parser *parse;

    if(std::string("-") == argv[1]) { parse = new Parser(std::cin); }
    else { parse = new Parser(argv[1]); }

    out << (*parse);

    out.flush();

    delete parse;

    return 0;
}

#endif // defined MAIN_H

