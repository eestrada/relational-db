#include "DataBase.h"

using namespace DB;
using namespace std;

Relation::Relation(const string &n, const Scheme &s) : name(n), scheme(s), tuples() {}

/*
Relation Relation::select(StrDict query) const
{

}
*/

Relation Relation::select(Index index, string value) const
{

}

Relation Relation::select(Index index1, Index index2) const
{

}

Relation Relation::project(const IndexList &indices) const
{

}

Relation Relation::unioned(const Relation &other) const
{

}

Relation Relation::join(const Relation &other) const
{

}

void Relation::insert(Tuple t)
{
	auto ret = tuples.insert(t);

	if(ret.second == false) {} // Possibly throw exception if insert fails
}

Relation Relation::rename(StrDict mapping) const
{

}

string Relation::get_name() const { return name; }
Scheme Relation::get_scheme() const { return scheme; }
TupleSet Relation::get_tuples() const {	return tuples; }

Relation& DataBase::operator[](string name)
{
    return relations.at(name);
}

void DataBase::insert(Relation r)
{
    relations.insert({r.get_name(), r});
}
