#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include "OrderedSet.h"


namespace DG
{

using namespace std;

typedef vector<string> StrList;

struct Node : set< string >
{
	Node() : id(), visited(false), postorder(){}
	string id;
	bool visited;
	int postorder;
};

struct Graph : map< string, Node >
{
	Graph(): cpo(0){}
	void reset();
	StrList depth_search(const string &rootid);
	StrList& sorted(StrList& slist) const;
	int cpo;
};

}

#endif // end include guard
