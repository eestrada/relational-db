#include "Parser.h"
#include <iostream>

namespace Parse
{
using namespace std;

string Parameter::get_ident() const
{
    if (type != Type::IDENT) throw parsing_error("Parm is not identifier.");
    return str;
}

string Parameter::get_literal() const
{
    if (type != Type::STRING) throw parsing_error("Parm is not string literal");
    return '\'' + str + '\'';
}

Parameter::operator string() const
{
    try
    {
        return this->get_ident();
    }
    catch(const parsing_error &e)
    {
        return this->get_literal();
    }
}

Predicate::operator string() const
{
    ostringstream out;
    out << string(ident) << '(';

    for(auto parm : parm_vec)
    {
        out << string(parm) << ',';
    }

    if(parm_vec.size() > 0)
    {
        string retval = out.str();
        retval.back() = ')';
        return retval;
    }
    else
    {
        out << ')';
        return out.str();
    }
}

Rule::operator string() const
{
    ostringstream out;
    out << string(pred) << " :- ";

    for(auto pred : pred_list)
    {
        out << string(pred) <<',';
    }
    string retval = out.str();

    if(retval.back() == ',') retval.pop_back();
    return retval;
}

DatalogProgram::operator string() const
{
    ostringstream out;

    out << "Schemes(" << Schemes.size() << "):\n";
    for(auto pred : Schemes)
        out << "  " << string(pred) << "\n";

    out << "Facts(" << Facts.size() << "):\n";
    for(auto pred : Facts)
        out << "  " << string(pred) << "\n";

    out << "Rules(" << Rules.size() << "):\n";
    for(auto rule : Rules)
        out << "  " << string(rule) << "\n";

    out << "Queries(" << Queries.size() << "):\n";
    for(auto pred : Queries)
        out << "  " << string(pred) << "\n";

    out << "Domain(" << Domain.size() << "):\n";
    for(auto str : Domain)
        out << "  " << string(str) << "\n";

    return out.str();
}

void DatalogProgram::build_domain()
{
    for(auto pred : Schemes)
    {
        for(auto parm : pred.parm_vec)
        {
            try { Domain.insert(parm.get_literal()); }
            catch(const parsing_error &e) { continue; }
        }
    }

    for(auto pred : Facts)
    {
        for(auto parm : pred.parm_vec)
        {
            try { Domain.insert(parm.get_literal()); }
            catch(const parsing_error &e) { continue; }
        }
    }

    for(auto rule : Rules)
    {
        for(auto pred : rule.pred_list)
        {
            for(auto parm : pred.parm_vec)
            {
                try { Domain.insert(parm.get_literal()); }
                catch(const parsing_error &e) { continue; }
            }
        }
    }

    for(auto pred : Queries)
    {
        for(auto parm : pred.parm_vec)
        {
            try { Domain.insert(parm.get_literal()); }
            catch(const parsing_error &e) { continue; }
        }
    }
    return;
}

void Parser::parse_DatalogProgram()
{
    string err = "Unexpected token.";
    //if (lexer->current().kind == Lex::Kind::START_OF_STRM)
    lexer->next();

    if (lexer->current().kind != Lex::Kind::SCHEMES || 
        lexer->next().kind != Lex::Kind::COLON)
            throw syntax_error(err, lexer->current());
    else
    {
        lexer->next();
        check_kind(Lex::Kind::ID);
        parse_Scheme_list();
    }

    if (lexer->current().kind != Lex::Kind::FACTS || 
        lexer->next().kind != Lex::Kind::COLON)
            throw syntax_error(err, lexer->current());
    else
    {
        lexer->next();
        parse_Facts_list();
    }

    if (lexer->current().kind != Lex::Kind::RULES || 
        lexer->next().kind != Lex::Kind::COLON)
            throw syntax_error(err, lexer->current());
    else
    {
        lexer->next();
        parse_Rules_list();
    }

    if (lexer->current().kind != Lex::Kind::QUERIES || 
        lexer->next().kind != Lex::Kind::COLON)
            throw syntax_error(err, lexer->current());
    else
    {
        lexer->next();
        check_kind(Lex::Kind::ID);
        parse_Queries_list();
    }

    if (lexer->current().kind != Lex::Kind::END_OF_STRM) 
        throw syntax_error(err, lexer->current());

    dlprog->build_domain();
}

void Parser::parse_Scheme_list()
{
    if (lexer->current().kind != Lex::Kind::ID) return; 
    auto scheme = parse_Predicate();
    dlprog->Schemes.push_back(scheme);
    parse_Scheme_list();
}

void Parser::parse_Facts_list()
{
    if (lexer->current().kind != Lex::Kind::ID) return; 
    auto fact = parse_Predicate();
    check_kind(Lex::Kind::PERIOD);
    dlprog->Facts.push_back(fact);
    lexer->next();
    parse_Facts_list();
}

void Parser::parse_Rules_list()
{
    if (lexer->current().kind != Lex::Kind::ID) return; 
    auto rule = parse_Rule();
    dlprog->Rules.push_back(rule);
    parse_Rules_list();
}

Rule Parser::parse_Rule()
{
    auto pred = parse_Predicate();
    check_kind(Lex::Kind::COLON_DASH);
    lexer->next();
    auto pred_list = parse_Predicate_list();
    check_kind(Lex::Kind::PERIOD);
    lexer->next();

    return Rule{pred, pred_list};

}

void Parser::parse_Queries_list()
{
    if (lexer->current().kind != Lex::Kind::ID) return; 
    auto query = parse_Predicate();
    check_kind(Lex::Kind::Q_MARK);
    dlprog->Queries.push_back(query);
    lexer->next();
    parse_Queries_list();
}

vector<Predicate> Parser::parse_Predicate_list()
{
    vector<Predicate> pred_list;

    try
    {
        while(true)
        {
            try
            {
                pred_list.push_back(parse_Predicate());
            }
            catch(const syntax_error &e)
            {
                if(e.token().kind == Lex::Kind::COMMA) lexer->next();
                else throw;
            }
        }
    }
    catch(const syntax_error &e)
    {
        if(e.token().kind == Lex::Kind::PERIOD) return pred_list;
        else throw;
    }

}

Predicate Parser::parse_Predicate()
{
    check_kind(Lex::Kind::ID);

    string id = lexer->current().value;

    lexer->next();
    check_kind(Lex::Kind::LEFT_PAREN);

    lexer->next();
    auto parm_vec = parse_Parameter_list();

    check_kind(Lex::Kind::RIGHT_PAREN);
    lexer->next();

    return Predicate{id, parm_vec};
}

vector<Parameter> Parser::parse_Parameter_list()
{
    using Parameter::Type::IDENT;
    using Parameter::Type::STRING;

    vector<Parameter> retval;

    auto t = lexer->current();
    if (t.kind != Lex::Kind::ID &&
        t.kind != Lex::Kind::STRING) 
        throw syntax_error("Unexpected token.", lexer->current());

    auto parm_type = (t.kind == Lex::Kind::ID) ? IDENT : STRING; 
    auto val = t.value;

    retval.push_back({parm_type, val});

    while(lexer->next().kind == Lex::Kind::COMMA)
    {
        auto t = lexer->next();
        if (t.kind != Lex::Kind::ID &&
            t.kind != Lex::Kind::STRING) 
            throw syntax_error("Unexpected token.", lexer->current());

        auto parm_type = (t.kind == Lex::Kind::ID) ? IDENT : STRING; 
        auto val = t.value;

        retval.push_back({parm_type, val});
    }

    return retval;
}

Parameter Parser::parse_Parameter()
{

}

void Parser::check_kind(Lex::Kind k)
{
    if(lexer->current().kind != k)
        throw syntax_error(lexer->current());
}

Parser::Parser(shared_ptr<Lex::Lexer> l) : lexer(l) {}

void Parser::parse()
{
    dlprog = shared_ptr<DatalogProgram>(new DatalogProgram);
    parse_DatalogProgram();
    return;
}

shared_ptr<const DatalogProgram> Parser::get_DatalogProgram() const
{
    // if(not dlprog) this->parse(); // non-const
    return dlprog;
}

}
