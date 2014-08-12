#include "Interpreter.h"
#include "DataBase.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <ciso646>
#include <queue>
#include <algorithm>
#include <functional>

using namespace DB;
using namespace DG;
using namespace std;
using namespace Interpret;
using namespace Parse;

Interpreter::Interpreter(const string &file)
  : parser(new Parse::Parser(file)), db(), out(), dgout()
{
	this->interpret();
}

Interpreter::Interpreter(istream &input_stream)
  : parser(new Parse::Parser(input_stream)), db(), out(), dgout()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<istream> input_stream)
  : parser(new Parse::Parser(move(input_stream))), db(), out(), dgout()
{
	this->interpret();
}

Interpreter::Interpreter(unique_ptr<Parser> &&p)
  : parser(move(p)), db(), out(), dgout()
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
		build_query_output(pred);
		/*
		Relation r = interpret_query(db[pred.ident], pred);

		out << query_to_scheme(pred) << "? ";

		auto size = r.get_tuples().size();
		if(size == 0) out << "No\n";
		else out << "Yes(" << size << ")\n";
		out << r;
		*/
	}
}

void Interpreter::build_Postorder(const string &qid)
{
	// postorder

	// Topo sort
}

void Interpreter::build_query_output(const Predicate &pred)
{
	auto qs =  query_to_scheme(pred);

	// Graph output
	out << qs << "?\n\n";

	out << "  Postorder Numbers\n";
	graph.reset();
   	auto deplist = graph.depth_search(qidmap.at(qs.name));
	for(const auto &id : deplist)
	{
		out << "    " << id << ": " << graph.at(id).postorder <<"\n";
	}
//	build_Postorder(qidmap.at(pred.ident));
	out << "\n";

	out << "  Rule Evaluation Order\n";
	auto sortedlist = deplist;
	sortedlist = graph.sorted(sortedlist);
	for(const auto &id : sortedlist)
	{
		if(id.front() != 'Q') out << "    " << id <<"\n";
	}
	out << "\n";

	out << "  Backward Edges\n";
	sort(deplist.begin(), deplist.end());
	for(const auto &s : deplist)
	{
		priority_queue< string, deque<string>, greater<string> > pq;
		for(const auto &d : graph.at(s))
			if(graph[d].postorder < graph[s].postorder)pq.push(d);

//		if(pq.size() > 0)
//			out << "    " << s <<
	}
	// do backward edges work here
	out << "\n";

	out << "  Rule Evaluation\n";
	// do rule eval work here
	out << "\n";

	// Query output
	Relation r = interpret_query(db[pred.ident], pred);

	out << qs << "? ";

	auto size = r.get_tuples().size();
	if(size == 0) out << "No\n";
	else out << "Yes(" << size << ")\n";
	out << r;
	out << "\n";
}


void Interpreter::build_graph_output()
{
	dgout << "Dependency Graph\n";

	for(const auto &p : graph)
	{
		dgout << "  " << p.first << ":";
		for(const auto &v : p.second)
		{
			dgout << " " << v;
		}
		dgout << "\n";
	}
	dgout << "\n";

	/*
	auto dlprog = parser->get_DatalogProgram();

	auto qcnt = 1;
	for(const auto &query : dlprog->Queries)
	{
		dgout << query_to_scheme(query) << "?\n\n";
		++qcnt;
	}
	return;
	*/
}

void Interpreter::build_graph()
{
	auto dlprog = parser->get_DatalogProgram();

	auto qcnt = 1;
	for(const auto &query : dlprog->Queries)
	{
		DG::Node qnode;
		qnode.id = "Q" + to_string(qcnt);

		auto rcnt = 1;
		for(const auto &rule : dlprog->Rules)
		{
			auto rid = "R" + to_string(rcnt);
			if(rule.pred.ident == query.ident)
              {
				qnode.insert(rid);
              }
            ++rcnt;
		}
		graph[qnode.id] = qnode;
		qidmap[query.ident] = qnode.id;
		ridmap[qnode.id] = query.ident;
        ++qcnt;
	}


	auto r1cnt = 1;
	for(const auto &rule1 : dlprog->Rules)
	{
		DG::Node rnode;
		rnode.id = "R" + to_string(r1cnt);

		for(const auto &rbody : rule1.pred_list)
		{
			auto r2cnt = 1;
			for(const auto &rule2 : dlprog->Rules)
			{
				auto rid = "R" + to_string(r2cnt);
				if(rbody.ident == rule2.pred.ident)
				{
					rnode.insert(rid);
				}
				++r2cnt;
			}
        }
		graph[rnode.id] = rnode;
        ++r1cnt;
	}

	build_graph_output();
}

DataBase Interpreter::get_database() const { return db; }

string Interpreter::get_query_output() const { return dgout.str() + out.str(); }

void Interpreter::interpret()
{
	parser->parse();

	terp_schemes();
	terp_facts();
	// out << "Converged after " << terp_rules() << " passes through the Rules.\n";
	terp_rules();
	build_graph();
	terp_queries();
}
