// -*- C++ -*-
#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "Parser.h"
#include "DataBase.h"
#include "Graph.h"
#include <memory>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace Interpret
{

using namespace std;
using namespace Parse;
using namespace DB;

struct RuleQuery 
{
	Scheme rule;
	vector<Scheme> schemes;
};


template <typename T>
class counter_template
{
public:
	void increment(const T &key) { countmap[key] += 1; }

	size_t get_val(const T &key) const { return countmap.at(key); }

	size_t get_max() const
	{
		size_t retval = 0;
		for(auto p : countmap) if(p.second > retval) retval = p.second;
		return retval;
	}

	size_t get_sum() const
	{
		size_t retval = 0;
		for(auto p : countmap) retval += p.second;
		return retval;
	}

private:
	::std::map<T, size_t> countmap;
};

typedef counter_template<string> Counter;

class Interpreter
{
public:
    Interpreter(const string &input_file_path);
    Interpreter(istream &input_stream);
    Interpreter(unique_ptr<istream> input_stream);
	Interpreter(unique_ptr<Parser> &&p);
	Interpreter(const Interpreter &other) = delete;
	Interpreter(Interpreter &&other) = delete;
	Interpreter& operator=(const Interpreter &other) = delete;
	Interpreter& operator=(Interpreter &&other) = delete;
	DataBase get_database() const;
	string get_query_output() const;
private:
	void interpret();
	void terp_schemes();
	void terp_facts();
	size_t terp_rules(bool caller_count=1);
	bool terp_rule(const string &rid);
	void terp_rules_wrapper();
	void terp_queries();
	void build_graph();
	void build_graph_output();
	void build_query_output(const string &qid, const Predicate &pred);
	DG::StrList build_Postorder(const string &qid);
	DG::StrList build_Toposort(const DG::StrList &deplist);
	bool build_BackwardEdges(const DG::StrList &deplist);
private:
	unique_ptr<Parser> parser;
	DataBase db;
	ostringstream out;
	ostringstream dgout;
	DG::Graph graph;
	unordered_map<string, string> qidmap;
	unordered_map<string, int> ridmap;
};

}

#endif // End include guard
