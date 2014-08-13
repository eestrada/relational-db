#include "Graph.h"
#include <algorithm>

using namespace DG;
using namespace std;

bool compare_nodes(const Node &a, const Node &b)
{
	return a.postorder < b.postorder;
}

StrList & extend(StrList &self, const StrList &other)
{
	for(const auto &v : other)
	{
		self.push_back(v);
	}
	return self;
}

void Graph::reset()
{
	for(auto &p : *this)
	{
		p.second.visited = false;
	}
	cpo = 0;
}

StrList Graph::depth_search(const string &id)
{
	StrList retval;

	if(at(id).visited) return retval;
	else at(id).visited = true;
	retval.push_back(id);

	auto node = at(id);
	for(auto depid = node.cbegin(); depid != node.cend(); ++depid)
	{
		if(at(*depid).visited) continue;
		else
		{
			auto other = depth_search(*depid);
			retval = extend(retval, other);
		}
    }
	at(id).postorder = cpo += 1;
	
	return retval;
}

StrList & Graph::sorted(StrList & sl)const
{
	deque<Node> nl;
	for(const auto &s : sl)
	{
		nl.push_back(at(s));
	}

	sort(nl.begin(), nl.end(), compare_nodes);

	auto s = sl.size();
	for(auto i = 0; i < s; ++i)
	{
		sl[i] = nl[i].id;
	}

	return sl;
}
