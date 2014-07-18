#include "Driver.h"
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int Driver::lex(int argc, char **argv)
{
    vector<string> args(argv, argv+argc);

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

int Driver::parse(int argc, char **argv)
{
    vector<string> args(argv, argv+argc);
    
    ifstream fin(args.at(1));
    ofstream fout(args.at(2));
    
    unique_ptr<Lex::Lexer> l(new Lex::Lexer(fin));
    Parse::Parser p(move(l));

    try
    {
        p.parse();
    }
    catch(const Parse::syntax_error &e)
    {
        string tmp = "Failure!\n  " + string(e.token()) + "\n";
        fout << tmp;
        return EXIT_SUCCESS;
    }

    auto dlprog = p.get_DatalogProgram();
    fout << "Success!\n";
    fout << string(*dlprog);

    return EXIT_SUCCESS;
}

int Driver::interpret(int argc, char **argv)
{
    vector<string> args(argv, argv+argc);

    return EXIT_SUCCESS;
}
