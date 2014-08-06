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

void Interpreter::terp_schemes()
{
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

Relation interpret_query(const Relation &rel_in, const Predicate &pred)
{
	Relation r = rel_in;

	StrDict nmap;
	IndexList pil;
	map<string, Index> imap;
	auto scheme = r.get_scheme();
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
				if(iit != imap.end()) r = r.select(iit->second, i);
				nmap[scheme.at(i)] = pstr;
			}
			imap.emplace(pstr, i);
		}
		catch(const exception &e)
		{
			r = r.select(i, parm.get_literal());
		}
		++i;
	}

	r = r.project(pil);
	r = r.rename(nmap);

	return r;
}

size_t Interpreter::terp_rules(bool caller_count)
{
	if(caller_count == false) return false;

	auto dlprog = parser->get_DatalogProgram();

	size_t orig_size = db.db_size();

	for(auto rule : dlprog->Rules)
	{
		std::vector<Relation> rels;

		for(auto pred : rule.pred_list)
		{
			Relation r = interpret_query(db.at(pred.ident), pred);

			rels.push_back(r);
		}

		Relation result = rels.front();
		for(auto r : rels)
		{
			result = result.join(r);
			// result = result + r;
		}

		Relation final = db.at(rule.pred.ident);

		final = final.rename(query_to_scheme(rule.pred));
		final = final.unioned(result);
		// final = final | result;

		db[final.get_name()] = final;
	}

	return caller_count + this->terp_rules(orig_size < db.db_size());
}

void Interpreter::terp_queries()
{
	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Queries)
	{
		Relation r = interpret_query(db[pred.ident], pred);

		out << query_to_scheme(pred) << "? ";

		auto size = r.get_tuples().size();
		if(size == 0) out << "No\n";
		else out << "Yes(" << size << ")\n";
		out << r;
	}
}

DataBase Interpreter::get_database() const { return db; }

string Interpreter::get_query_output() const { return out.str(); }

void Interpreter::interpret()
{
	parser->parse();

	terp_schemes();
	terp_facts();
	out << "Converged after " << terp_rules() << " passes through the Rules.\n";
	terp_queries();
}
