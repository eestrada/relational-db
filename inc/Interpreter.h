#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "Parser.h"

namespace Interpret
{

class Interpreter
{
public:
	Interpreter(const Interpreter &other) = delete;
	Interpreter(Interpreter &&other) = delete;
	Interpreter& operator=(const Interpreter &other) = delete;
	Interpreter& operator=(Interpreter &&other) = delete;
	void interpret();
private:
	Parse::Parser parser;
};

}

#endif // End include guard
