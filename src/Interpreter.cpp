#include "Interpreter.h"
#include "DataBase.h"
#include <iostream>
#include <fstream>
#include <ciso646>

using namespace DB;
using namespace std;
using namespace Interpret;
using namespace Parse;

Interpreter::Interpreter(const string &file)
	: parser(new Parse::Parser(file)), db(), out() {}

Interpreter::Interpreter(istream &input_stream)
	: parser(new Parse::Parser(input_stream)), db(), out() {}


Interpreter::Interpreter(unique_ptr<istream> input_stream)
	: parser(new Parse::Parser(move(input_stream))), db(), out() {}


Interpreter::Interpreter(unique_ptr<Parser> &&p)
	: parser(move(p)), db(), out() {}

bool query_is_exact(const Predicate &pred)
{
	for(auto parm : pred.parm_vec)
	{
		if(parm.type != Parameter::Type::STRING) return false;
	}

	return true;
}

bool query_is_scheme(const Predicate &pred)
{
	for(auto parm : pred.parm_vec)
	{
		if(parm.type != Parameter::Type::IDENT) return false;
	}

	return true;
}

bool query_is_mixed(const Predicate &pred)
{
	bool str = false, ident = false;
	for(auto parm : pred.parm_vec)
	{
		if(parm.type == Parameter::Type::STRING) str = true;
		else if (parm.type == Parameter::Type::IDENT) ident = true;
		else throw runtime_error("Somehow, you have a non-existent type value.");
	}

	return str and ident;
}

void Interpreter::terp_schemes()
{
	// cout << "Terpin' schemes!" << endl;

	auto dlprog = parser->get_DatalogProgram();
	for(auto pred : dlprog->Schemes)
	{
		Scheme s;
		s.name = pred.ident;
		for(auto parm : pred.parm_vec)
		{
			s.push_back(parm.get_ident());
		}

		Relation r(s);

		db.insert(r);
	}
}

void Interpreter::terp_facts()
{
	// cout << "Terpin' facts!" << endl;
	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Facts)
	{
		Tuple t;
		for(auto parm : pred.parm_vec)
		{
			t.push_back(parm.get_literal());
		}

		db[pred.ident].insert(t);
	}
}

void Interpreter::terp_rules()
{
	// cout << "Terpin' rules!" << endl;
	// auto dlprog = parser->get_DatalogProgram();
}

Scheme query_to_scheme(Predicate p)
{
	Scheme ret;

	ret.name = p.ident;

	for(auto s : p.parm_vec)
	{
		ret.push_back(string(s));
	}

	return ret;
}

void Interpreter::terp_queries()
{
	// cout << "Terpin' queries!" << endl;
	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Queries)
	{
		bool uses_idents = false, uses_literals = false;
		StrDict nmap;
		IndexList il;
		Index i = 0;
		vector<string> qstr;
		auto scheme = db[pred.ident].get_scheme();
		for(auto parm : pred.parm_vec)
		{
			try
			{
				parm.get_ident();
				uses_idents = true;
				if(parm.get_ident() != scheme.at(i))
				{
					nmap[scheme.at(i)] = parm.get_ident();
				}
			}
			catch(...)
			{
				string val = parm.get_literal();
				qstr.push_back(val);
				il.push_back(i);
				uses_literals = true;
			}
			++i;
		}

		Relation r = db[pred.ident];
		for(Index ii = 0; ii < il.size(); ++ii)
		{
			r = r.select(il[ii], qstr[ii]);
		}

		if(nmap.size() > 0) r = r.rename(nmap);

		cout << boolalpha;
		cout << uses_literals << " ";
		cout << uses_idents << " ";
		cout << endl;

		if(uses_literals and uses_idents){}
		else if(uses_literals){}
		else if(uses_idents){}
		else { throw runtime_error("How can we have a query with nothing in it?") ;}

		out << query_to_scheme(pred) << "\n";
		out << r << "\n";
	}
}

DataBase Interpreter::get_database() const { return db; }

string Interpreter::get_output() const { return out.str(); }

void Interpreter::interpret()
{
	parser->parse();

	terp_schemes();
	terp_facts();
	terp_rules();
	terp_queries();
}
