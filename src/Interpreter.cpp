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
	: parser(new Parse::Parser(file)), db(), out(), passes()
{
	this->interpret();
}

Interpreter::Interpreter(istream &input_stream)
	: parser(new Parse::Parser(input_stream)), db(), out(), passes()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<istream> input_stream)
	: parser(new Parse::Parser(move(input_stream))), db(), out(), passes()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<Parser> &&p)
	: parser(move(p)), db(), out(), passes()
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
	// Relation r = db[pred.ident];
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

	// out << query_to_scheme(pred) << "? ";

	// auto size = r.get_tuples().size();
	// if(size == 0) out << "No\n";
	// else if(size > 0) out << "Yes(" << size << ")\n";
	// out << r;

	return r;
}

void Interpreter::terp_rules()
{
	auto dlprog = parser->get_DatalogProgram();

	Counter count;

	for(auto rule : dlprog->Rules)
	{
		std::vector<Relation> rels;

		for(auto pred : rule.pred_list)
		{
			Relation r = interpret_query(db.at(pred.ident), pred);

			rels.push_back(r);
		}

		Relation result = rels.front();

		if (rels.size() > 1)
		{
			for(auto r : rels)
			{	
				result = result.join(r);
			}
		}
		else if(rels.size() < 1)
		{
			throw runtime_error("A rule must have at least one predicate.");
		}

		Relation final;

		if(db.has(rule.pred.ident))
		{
			final = db.at(rule.pred.ident);
		}
		else
		{
			final = Relation(query_to_scheme(rule.pred));
		}

		final = final.unioned(result);

		db[final.get_name()] = final;

		count.increment(final.get_name());
	}

	out << "Converged after " << count.get_sum() << " passes through the Rules.\n";
}

void Interpreter::terp_queries()
{
	// cout << "Terpin' queries!" << endl;
	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Queries)
	{
		Relation r = interpret_query(db[pred.ident], pred);

		out << query_to_scheme(pred) << "? ";

		auto size = r.get_tuples().size();
		if(size == 0) out << "No\n";
		else if(size > 0) out << "Yes(" << size << ")\n";
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
	terp_rules();
	terp_queries();
}
