#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> create_args(int argc, char **argv)
{
    std::vector<std::string> v;
    for(int i = 0; i < argc; ++i)
    {
        v.push_back(std::string(argv[i]));
    }
    return v;
}

int main(int argc, char **argv)
{
    using namespace std;

    vector<string> args = create_args(argc, argv);

    ifstream fin(args.at(1));
    ofstream fout(args.at(2));
    //Lex::Lexer l(std::cin);
    Lex::Lexer l(fin);
    //cerr << "Input file: " << args.at(1) << endl;
    //cerr << "Output file: " << args.at(2) << endl;
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
        return EXIT_FAILURE;
    }
    fout << "Total Tokens = " << count << endl;

    /*
    Lex::Token t;
    t.kind = Lex::Kind::SCHEMES;
    cout << string(t) << endl;
    */
    
    return EXIT_SUCCESS;
}

