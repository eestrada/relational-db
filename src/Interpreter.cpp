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
	out << "Scheme Evaluation\n\n";
	auto dlprog = parser->get_DatalogProgram();
	for(auto &pred : dlprog->Schemes)
	{
		Scheme s;
		s.name = pred.ident;
		for(auto &parm : pred.parm_vec)
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
	
	for(auto &pred : dlprog->Facts)
	{
		Tuple t;
		for(auto &parm : pred.parm_vec)
		{
			t.push_back(parm.get_literal());
		}
		db[pred.ident].insert(t);
	}

	for(auto &rit : db)
	{
		out << rit.first << "\n";
		for(auto &t : rit.second.get_tuples())
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

	for(auto &s : p.parm_vec)
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
	for(auto &parm : pred.parm_vec)
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

		for(auto &pred : rule.pred_list)
		{
			Relation r = db.at(pred.ident);
			r = interpret_query(pred, r, r, r);

			rels.push_back(r);
		}

		// We do "rels.begin() + 1" to skip the first relation since "result"
		// already holds it. That way we don't pointlessly join identical
		// relations, which wastes a lot of compute power/time.
		Relation result = rels.front();
		for(auto iter = rels.begin() + 1; iter != rels.end(); ++iter)
		{
			result = result + *iter; // join
		}

		auto name = rule.pred.ident;
		Relation final = db.at(name);

		final.rename_update(query_to_scheme(rule.pred));
		final |= result; // in place union

		auto &s = db.at(name).get_scheme();
		final.rename_update(s);
		final -= db.at(name); // in place difference

		out << string(rule) << "\n";
		out << string(final);

		db.at(name) |= final; // in place union
	}

	return caller_count + this->terp_rules(orig_size != db.db_size());
}

void Interpreter::terp_queries()
{
	out << "Query Evaluation\n\n";
	auto dlprog = parser->get_DatalogProgram();

	auto qcnt = 1;		
	for(auto pred : dlprog->Queries)
	{
		build_query_output("Q" + to_string(qcnt), pred);
		++qcnt;
	}
}

void Interpreter::build_Postorder(const string &qid)
{
	// postorder

	// Topo sort
}

void Interpreter::build_query_output(const string &qid, const Predicate &pred)
{
	auto qs =  query_to_scheme(pred);

	// Graph output
	out << qs << "?\n\n";

	// Depth-First Search
	// Postorder
	out << "Postorder Numbers\n";
	graph.reset();
   	auto deplist = graph.depth_search(qid);
	sort(deplist.begin(), deplist.end());
	for(const auto &id : deplist)
	{
		out << "  " << id << ": " << graph.at(id).postorder <<"\n";
	}
	out << "\n";

	// Topological Sort
	// Rule Evaluation Order
	out << "Rule Evaluation Order\n";
	auto sortedlist = deplist;
	sortedlist = graph.sorted(sortedlist);
	decltype(sortedlist) topo_sorted;
	for(const auto &id : sortedlist)
	{
		if(id.front() != 'Q')
		{
			out << "  " << id <<"\n";
			topo_sorted.push_back(id);
		}
	}
	out << "\n";

	// Cycle Finding
	// Backward Edges
	out << "Backward Edges\n";
	for(const auto &s : deplist)
	{
		priority_queue< string, deque<string>, greater<string> > pq;

		if(s.front() != 'Q')
		{
			for(const auto &d : graph.at(s))
			{
				if(graph[d].postorder >= graph[s].postorder) pq.push(d);
			}
		}

		if(not pq.empty())
		{
			out << "  " << s << ":";
			while(not pq.empty())
			{
				out << " " << pq.top();
				pq.pop();
			}
			out << "\n";
		}
	}
	out << "\n";

	// Rule Evaluation
	out << "Rule Evaluation\n";
	bool eval_again = true;
	for(auto iter = topo_sorted.cbegin(); eval_again and iter != topo_sorted.cend(); )
	{
		eval_again = terp_rule(*iter);
		if(++iter == topo_sorted.cend() and not eval_again) iter = topo_sorted.cbegin();
	}
	// do rule eval work here
	out << "\n";

	// Query output
	Relation selection_rel = db.at(pred.ident);
	Relation projection_rel, rename_rel;
	rename_rel = interpret_query(pred, selection_rel, projection_rel, rename_rel);

	out << qs << "? ";
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

bool Interpreter::terp_rule(const string &rid)
{
	auto dlprog = parser->get_DatalogProgram();

	auto i = ridmap.at(rid);
	auto rule = dlprog->Rules.at(i);
	auto r = db[rule.pred.ident];

	out << "" << string(rule) << "\n";

//	if(caller_count == false) return false;

//	auto dlprog = parser->get_DatalogProgram();

	size_t orig_size = db.db_size();

//	for(auto rule : dlprog->Rules)
	{
		std::vector<Relation> rels;

		for(auto pred : rule.pred_list)
		{
			Relation r = db.at(pred.ident);
			r = interpret_query(pred, r, r, r);

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

//	return orig_size != db.db_size();
	return orig_size < db.db_size();
//	return caller_count + this->terp_rules(orig_size < db.db_size());
}

void Interpreter::build_graph_output()
{
	out << "Dependency Graph\n";

	for(const auto &p : graph)
	{
		out << "  " << p.first << ":";
		for(const auto &v : p.second)
		{
			out << " " << v;
		}
		out << "\n";
	}
	out << "\n";
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
		qidmap[qnode.id] = query.ident;
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
//		ridmap[rnode.id] = rule1.pred.ident;
		ridmap[rnode.id] = r1cnt - 1;
        ++r1cnt;
	}

	build_graph_output();
}

DataBase Interpreter::get_database() const { return db; }

string Interpreter::get_query_output() const { return out.str(); }

void Interpreter::terp_rules_wrapper()
{
	out << "Rule Evaluation\n\n";
	auto passes = terp_rules();

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
	build_graph();
	//terp_rules_wrapper();
	terp_queries();
}
