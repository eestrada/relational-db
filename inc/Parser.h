#ifndef __PARSER_H__
#define __PARSER_H__
#include "Lexer.h"
#include <memory>
#include <string>
#include <istream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <set>

namespace Parse
{

using namespace std;

class parsing_error : public std::runtime_error
{
public:
    parsing_error(const string &msg) : std::runtime_error(msg){}
};

class syntax_error : public parsing_error
{
public:
    syntax_error(const string &msg, const Lex::Token &t)
        : parsing_error(msg), tok(t){}

    syntax_error(const Lex::Token &t)
        : parsing_error("Unexpected token."), tok(t){}

    virtual intmax_t line_number() const {return tok.lnum;}
    virtual Lex::Token token() const {return tok;}

private:
    Lex::Token tok;
};

struct Parameter
{
    // internal types
    enum class Type : char {IDENT, STRING};
    // variables
    Type type;
    string str;

    string get_ident() const;
    string get_literal() const;
    explicit operator string() const;
};

struct Predicate
{
    string ident;
    vector<Parameter> parm_vec;

    explicit operator string() const;
};

struct Rule
{
    Predicate pred;
    vector<Predicate> pred_list;

    explicit operator string() const;
};

struct DatalogProgram
{
    vector<Predicate> Schemes;
    vector<Predicate> Facts;
    vector<Rule> Rules;
    vector<Predicate> Queries;
    set<string> Domain;

    explicit operator string() const;
    void build_domain();
};

class Parser
{
public:
    explicit Parser(unique_ptr<Lex::Lexer> &&l);
    void parse();
    shared_ptr<const DatalogProgram> get_DatalogProgram() const;
private: // functions
    void parse_DatalogProgram();
    void parse_Scheme_list();
    void parse_Facts_list();
    void parse_Rules_list();
    Rule parse_Rule();
    void parse_Queries_list();
    vector<Predicate> parse_Predicate_list();
    Predicate parse_Predicate();
    vector<Parameter> parse_Parameter_list();
    Parameter parse_Parameter();
    void check_kind(Lex::Kind k);
private: // variables
    unique_ptr<Lex::Lexer> lexer;
    shared_ptr<DatalogProgram> dlprog;
};

}

#endif // End include guard
