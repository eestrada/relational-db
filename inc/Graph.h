#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <set>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

namespace DG
{

using namespace std;

struct Graph;
struct Node;

  struct Graph : map< string,  shared_ptr<Node> >
{
	bool add(const Node &n);
	bool add(Node &&n);
};

struct Node
{
	string id;
	bool visited;
	int postorder;
	set< weak_ptr<Node> > deps;

	bool add(const Node &n);
	bool add(Node &&n);
	virtual const string& ntype() const = 0;
};

struct Query : Node
{
	virtual const string& ntype() const;
};

struct Rule : Node
{
	virtual const string& ntype() const;
};

}

#endif // end include guard
