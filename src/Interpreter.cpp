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

	for(auto rit : db)
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

Relation interpret_query(const Predicate &pred, Relation &selection_rel, Relation &projection_rel, Relation &rename_rel)
{
	StrDict nmap;
	IndexList pil;
	map<string, Index> imap;
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
				if(iit != imap.end()) selection_rel = selection_rel.select(iit->second, i);
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

	projection_rel = selection_rel.project(pil);
	rename_rel = projection_rel.rename(nmap);

	return rename_rel;
}

size_t Interpreter::terp_rules(bool caller_count)
{
	if(caller_count == false) return false;

	auto dlprog = parser->get_DatalogProgram();

	size_t orig_size = db.db_size();

	for(auto &rule : dlprog->Rules)
	{
		std::vector<Relation> rels;

		for(auto pred : rule.pred_list)
		{
			Relation r = db.at(pred.ident);
			r = interpret_query(pred, r, r, r);

			rels.push_back(r);
		}

		Relation result = rels.front();
		// Relation result(rels.front().get_scheme());
		for(auto r : rels)
		{
			result = result.join(r);
		}

		auto name = rule.pred.ident;
		Relation final = db.at(name);

		final = final.rename(query_to_scheme(rule.pred));
		final = final.unioned(result);
		// final = final | result;
		auto s = db.at(name).get_scheme();
		final = final.rename(s);

		out << string(rule) << "\n";
		// if (not first and final.size() != db.at(name).size() )

		if (final.size() != db.at(name).size() )
		{
			auto diff = final.difference(db.at(name));
			// cerr << "Comparing joined relations...\n";
			// cerr << string(db.at(name)) << "\n";
			// cerr << string(final) << "\n";
			out << string(diff);
		}

		db.at(name) = final;
	}

	return caller_count + this->terp_rules(orig_size != db.db_size());
}

void Interpreter::terp_queries()
{
	out << "Query Evaluation\n\n";
	auto dlprog = parser->get_DatalogProgram();
	
	for(auto pred : dlprog->Queries)
	{
		// Relation rename_rel = interpret_query(db[pred.ident], pred);
		Relation selection_rel = db[pred.ident];
		Relation projection_rel, rename_rel;
		rename_rel = interpret_query(pred, selection_rel, projection_rel, rename_rel);

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

void Interpreter::terp_rules_wrapper()
{
	out << "Rule Evaluation\n\n";
	auto passes = terp_rules();

	// auto dlprog = parser->get_DatalogProgram();
	// for(auto &rule : dlprog->Rules)
	// {
	// 	auto &rel = db[rule.pred.ident];
	// 	if (rel.get_tuples().size())
	// 	{
	// 		out << string(rule) << "\n";

	// 		out << rel << "";
	// 	}

	// }

	// for(auto &rule : dlprog->Rules)
	// {
	// 	out << string(rule) << "\n";
	// }
	out << "\n";

	out << "Converged after " << passes << " passes through the Rules.\n\n";

	for(auto &p : db)
	{
		out << p.first << "\n";

		out << string(p.second) << "\n";
	}
}


void Interpreter::interpret()
{
	parser->parse();

	terp_schemes();
	terp_facts();
	terp_rules_wrapper();
	terp_queries();
}
