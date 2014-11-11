#include "Interpreter.h"
#include "DataBase.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <ciso646>

using namespace DB;
using namespace std;
using namespace Interpret;
using namespace Parse;

Interpreter::Interpreter(const string &file)
	: parser(new Parse::Parser(file)), db(), out()
{
	this->interpret();
}

Interpreter::Interpreter(istream &input_stream)
	: parser(new Parse::Parser(input_stream)), db(), out()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<istream> input_stream)
	: parser(new Parse::Parser(move(input_stream))), db(), out()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<Parser> &&p)
	: parser(move(p)), db(), out()
{
	this->interpret();
}

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
	out << "Scheme Evaluation\n\n";

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
	out << "Fact Evaluation\n\n";

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

	for(auto rit : db.relations)
	{
		out << rit.first << "\n";
		for(auto t : rit.second.get_tuples())
		{
			out << " ";
			for (int i = 0; i < t.size(); ++i)
			{
				out << " ";
				out << rit.second.get_scheme()[i];
				out << "=";
				out << t[i];
			}
			out << "\n";
		}
		out << "\n";
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
	out << "Query Evaluation\n\n";

	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Queries)
	{
		StrDict nmap;
		IndexList pil;
		map<string, Index> imap;
		Relation selection_rel = db[pred.ident];
		auto scheme = selection_rel.get_scheme();
		Index i = 0;

		for(auto parm : pred.parm_vec)
		{
			try
			{
				auto pstr = parm.get_ident();
				pil.push_back(i);
				if(pstr != scheme.at(i))
				{
					auto iit = imap.find(pstr);
					if(iit != imap.end())
					{
						selection_rel = selection_rel.select(iit->second, i);
						pil.pop_back(); // don't project repeated identifiers
					}
					nmap[scheme.at(i)] = pstr;
				}
				imap.emplace(pstr, i);
			}
			catch(const exception &e)
			{
				selection_rel = selection_rel.select(i, parm.get_literal());
			}
			++i;
		}
		Relation projection_rel = selection_rel.project(pil);
		Relation rename_rel = projection_rel.rename(nmap);

		out << query_to_scheme(pred) << "? ";
		auto size = rename_rel.get_tuples().size();
		if(size == 0) out << "No\n";
		else if(size > 0)
		{
			out << "Yes(" << size << ")\n";
			out << "select\n";
			out << selection_rel;
			out << "project\n";
			out << projection_rel;
			out << "rename\n";
			out << rename_rel;
		}
		out << "\n";
	}
}

DataBase Interpreter::get_database() const { return db; }

string Interpreter::get_query_output() const { return out.str(); }

void Interpreter::interpret()
{
	parser->parse();

	terp_schemes();
	terp_facts();
	terp_rules();
	terp_queries();
}
