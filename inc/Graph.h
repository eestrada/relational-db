#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <unordered_map>
#include <string>
#include "OrderedSet.h"

namespace DG
{

using namespace std;

struct Node : DB::OrderedSet< string >
{
	string id;
	bool visited;
	int postorder;
};

struct Graph : unordered_map< string, Node >
{
};

}

#endif // end include guard
