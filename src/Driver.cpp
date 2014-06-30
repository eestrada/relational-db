#include "Driver.h"
#include "Lexer.h"
#include "Parser.h"
#include <fstream>
#include <string>
#include <vector>

namespace Driver
{

std::vector<std::string> create_args(int argc, char **argv)
{
    std::vector<std::string> v;
    for(int i = 0; i < argc; ++i)
    {
        v.push_back(std::string(argv[i]));
    }
    return v;
}

}

int Driver::lex(int argc, char **argv)
{
    using namespace std;

    vector<string> args = create_args(argc, argv);

    ifstream fin(args.at(1));
    ofstream fout(args.at(2));
    Lex::Lexer l(fin);

    int count = 0;
    try
    {
        for(auto t = l.next(); t.kind != Lex::Kind::END_OF_STRM; t = l.next())
        {
            ++count;
            fout << string(t) << endl;
        }
    }
    catch(const Lex::input_error &e)
    {
        fout << "Input Error on line " << e.line_number() << endl;
        return EXIT_SUCCESS;
    }
    fout << "Total Tokens = " << count << endl;
    
    return EXIT_SUCCESS;
}

int Driver::parse(int argc, char **argv) {return 0;}

int Driver::interpret(int argc, char **argv) {return 0;}
