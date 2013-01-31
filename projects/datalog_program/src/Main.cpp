#include "Lex.h"
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

    Lex *lexer;

    if(dash == argv[1])
    {
        lexer = new Lex(cin);
    }
    else
    {
        lexer = new Lex(argv[1]);
    }

    Lex &lexref = *lexer;

    //cout << lexer->toString();
/*
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
    lexer->advance();
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
    cout << *(lexref.getCurrentToken());
*/

    try
    {
        int i = 0;
        while(true)
        {
            cout << lexref[i];
            ++i;
        }
    }
    catch(...)
    {
    }

    delete lexer; lexer = NULL;

    return 0;
}

