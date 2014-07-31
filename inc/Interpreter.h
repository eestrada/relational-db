#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "Parser.h"
#include "DataBase.h"
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
	void terp_rules();
	void terp_queries();
private:
	unique_ptr<Parser> parser;
	DataBase db;
	ostringstream out;
	std::map<string, RuleQuery> rulev;
};

}

#endif // End include guard
