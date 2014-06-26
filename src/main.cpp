#include "Lexer.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    using namespace std;

    cerr << "Dummy code for a place holder." << endl;

    Lex::Lexer l(std::cin);

    /*
    try
    {
        for(auto t = l.next(); t != Lex::Token::END_OF_STRM; t = l.next())
        {
            cout << string(t) << endl;
        }
    }
    catch(const Lex::input_error &e)
    {
    }
    catch(const Lex::end_of_stream &e)
    {
    }
    */

    Lex::Token t;
    t.kind = Lex::Kind::SCHEMES;
    cout << string(t) << endl;
    
    return EXIT_SUCCESS;
}

