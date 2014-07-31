#include "DataBase.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace DB;
using namespace std;

template <typename T, typename U>
ostream & operator<<(ostream &out, const pair<T,U> &p)
{
	out << "pair<\"" << p.first << "\", \"" << p.second << "\">";
	return out;
}

Scheme Scheme::join(const Scheme &a, const Scheme &b)
{
	Scheme retval;

	for (auto c : a)
	{
		cerr << c << endl;
	}
	return retval;
}

Relation::Relation(const Scheme &s) : scheme(s), tuples() {}

/*
Relation Relation::select(StrDict query) const
{

}
*/

Relation Relation::select(Index index, string value) const
{
	Relation r(this->scheme);

	for(auto t : this->tuples)
	{
		if(t.at(index) == value) r.insert(t);
	}

	return r;
}

Relation Relation::select(Index index1, Index index2) const
{
	Relation r(this->scheme);

	for(auto t : this->tuples)
	{
		if(t.at(index1) == t.at(index2)) r.insert(t);
	}
	
	return r;
}

Relation Relation::project(const IndexList &indices) const
{
	Scheme tmp_sch;
	tmp_sch.name = this->scheme.name;

	for(auto i : indices)
	{
		tmp_sch.push_back(this->scheme.at(i));
	}

	Relation retval;
	retval.scheme = tmp_sch;
	for(auto t : this->tuples)
	{
		Tuple nt;
		for(auto i : indices)
		{
			nt.push_back(t.at(i));
		}

		retval.insert(nt);
	}

	return retval;
}

Relation Relation::unioned(const Relation &other) const
{
	throw logic_error("unioned member function not implemented");
	return *this;
}

Relation Relation::join(const Relation &other) const
{

	// make the scheme s for the result relation
	Scheme jscheme = Scheme::join(this->scheme, other.scheme);
	//     (combine r1's scheme with r2's scheme)

	// make a new empty relation r using scheme s

	// for each tuple t1 in r1
	//     for each tuple t2 in r2

	// 	if t1 and t2 can join
	// 	    join t1 and t2 to make tuple t
	// 	    add tuple t to relation r
	// 	end if

	//     end for
	// end for


	Relation retval;
	throw logic_error("join member function not implemented");
	return *this;
}

void Relation::insert(Tuple t)
{
	auto ret = tuples.insert(t);

	if(ret.second == false) {} // Possibly throw exception if insert fails
}

Relation Relation::rename(StrDict mapping) const
{
	if(mapping.size() == 0) return *this;

	Relation retval = *this;
	Scheme new_scheme = this->scheme;

	for(auto i = new_scheme.begin(); i != new_scheme.end(); ++i)
	{
		try	{ mapping.at(*i); }
		catch(const out_of_range &e) { continue; }
		/* else */
		*i = mapping.at(*i);
	}

	retval.scheme = new_scheme;

	return retval;
}

string Relation::get_name() const { return scheme.name; }
Scheme Relation::get_scheme() const { return scheme; }
TupleSet Relation::get_tuples() const {	return tuples; }

Relation::operator string() const
{
	auto sch = this->get_scheme();

	// cout << sch.size() << endl;
	if(not sch.size()) return string();

	ostringstream out;
	for(auto t : this->get_tuples())
	{
		out << "  ";
		for(unsigned i = 0; i < sch.size(); ++i)
		{
			out << sch.at(i) <<"="<< t.at(i);

			if(i != sch.size()-1) out << ", ";
			else out << "\n";
		}
	}

	return out.str();

}

Relation& DataBase::operator[](string name)
{
    return relations.at(name);
}

void DataBase::insert(Relation r)
{
    relations.insert({r.get_name(), r});
}

DataBase::operator string() const
{
	ostringstream out;

	out << "Tables:\n";

	for(auto p : relations)
	{
		out << "\t" << p.second.get_scheme() << "\n";

		auto ts = p.second.get_tuples();

		for(auto t : ts)
		{
			out << "\t\t" << t << "\n";
		}
	}

	return out.str();
}

ostream & operator<<(ostream &out, const Scheme &s)
{
	out << s.name <<"(";

	for(auto str = s.begin(); str != s.end(); ++str)
	{
		out << *str;

		if(str+1 != s.end()) out << ",";
		else out << ")";
	}
	return out;
}

ostream & operator<<(ostream &out, const Tuple &t)
{
	out << "(";

	for(auto str = t.begin(); str != t.end(); ++str)
	{
		// out << "'" << *str << "'";
		out << *str;

		if(str+1 != t.end()) out << ",";
		else out << ")";
	}
	return out;
}

ostream & operator<<(ostream &out, const Relation &r)
{
	return out << string(r);
}
