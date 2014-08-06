#include "DataBase.h"
#include "OrderedSet.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace DB;
using namespace std;


class UnjoinableError : public runtime_error
{
public:
	UnjoinableError(const string &s) : runtime_error(s){}
};

template <typename T, typename U>
ostream & operator<<(ostream &out, const pair<T,U> &p)
{
	out << "pair<\"" << p.first << "\", \"" << p.second << "\">";
	return out;
}

void Scheme::join(const Scheme &other)
{
	OrderedSet<string> selfset(*this);

	selfset += OrderedSet<string>(other);

	this->resize(selfset.size());

	copy(selfset.cbegin(), selfset.cend(), this->begin());
}

Scheme Scheme::operator+(const Scheme &other) const
{
	Scheme retval = *this;

	retval.join(other);

	return retval;
}

Scheme& Scheme::operator+=(const Scheme &other)
{
	this->join(other);

	return *this;
}

Relation::Relation(const Scheme &s) : scheme(s), tuples() {}

Relation Relation::select(Index index, string value) const
{
	Relation r(this->scheme);

	for(auto t : this->tuples)
	{
		try
		{
			if(t.at(index) == value) r.insert(t);
		}
		catch(const exception &e)
		{
			throw;
		}
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

ostream & operator<<(ostream &out, const IndexList &indices)
{
	out << "[ ";
	for(auto i : indices)
	{
		out << i << ", ";
	}
	out << "]";
	return out;
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

	if(indices.size() == 0)
	{
		retval.tuples = this->tuples;
		return retval;
	}

	for(auto t : this->tuples)
	{
		Tuple nt;
		for(auto i : indices)
		{
			nt.push_back(t.at(i));
		}

		if(nt.size() > 0) retval.insert(nt);
	}

	return retval;
}

Relation Relation::unioned(const Relation &other) const
{
	Relation retval = *this;
	IndexList pil;

	Index i1 = 0;
	for(auto s1 : retval.scheme)
	{
		Index i2 = 0;
		for(auto s2 : other.scheme)
		{
			if (s1 == s2) pil.push_back(i2);
			++i2;
		}
		++i1;
	}

	Relation fixed = other.project(pil);

	for (auto t : fixed.tuples)	{ retval.insert(t);	}

	return retval;
}

Tuple join_tuples(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2)
{
	Tuple retval;

	// Check for joinability. Then append values from t1 that are either unique
	// based on the Scheme or match t2 based on the Scheme. If the Schemes
	// match columns, but the tuples do not match values, throw an exception.
	for(auto i1 = 0; i1 < s1.size(); ++i1)
	{
		retval.push_back(t1.at(i1)); // Assume tuples will be joinable.

		for(auto i2 = 0; i2 < s2.size(); ++i2)
		{
			if(s1.at(i1) == s2.at(i2))
			{
				if (t1.at(i1) == t2.at(i2)) break;
				else throw UnjoinableError(string("Tuples cannot be joined:"));
			}
		}
	}

	// Add remaining values from t2 based on uniqueness of Scheme columns.
	for(auto i2 = 0; i2 < s2.size(); ++i2)
	{
		bool unique = true;

		for(auto i1 = 0; i1 < s1.size(); ++i1)
		{
			if(s2.at(i2) == s1.at(i1))
			{
				unique = false;
				break;
			}
		}
		if(unique) retval.push_back(t2.at(i2));
	}

	return retval;
}

Relation Relation::join(const Relation &other) const
{
	Scheme jscheme = this->scheme + other.scheme;

	Relation retval(jscheme);

	for(auto t1 : this->tuples)
	{
		for(auto t2 : other.tuples)
		{
			try
			{
				auto t = join_tuples(t1, t2, this->scheme, other.scheme);
				retval.insert(t);
			}
			catch(const UnjoinableError &e){} //pass
		}
	}

	return retval;
}

void Relation::insert(Tuple t)
{
	// if(t.size() != scheme.size()) throw runtime_error("Tuple length does not match Scheme length.");
	auto ret = tuples.insert(t);
	// if(ret.second == false) {} // Possibly throw exception if insert fails
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

Relation Relation::rename(Scheme new_names) const
{
	if(new_names.size() != this->scheme.size())
		throw runtime_error("Scheme lengths do not match");

	Relation retval = *this;

	retval.scheme = new_names;

	return retval;
}

string Relation::get_name() const { return scheme.name; }
Scheme Relation::get_scheme() const { return scheme; }
TupleSet Relation::get_tuples() const {	return tuples; }

Relation::operator string() const
{
	auto sch = this->get_scheme();

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
    return this->at(name);
}

void DataBase::insert(Relation r)
{
    map<string, Relation>::insert({r.get_name(), r});
}

bool DataBase::has(string name) const {	return this->count(name); }

size_t DataBase::db_size() const
{
	size_t retval = 0;
	for(auto p : *this)
	{
		retval += p.second.get_tuples().size();
	}
	return retval;
}


DataBase::operator string() const
{
	ostringstream out;

	out << "Tables:\n";

	for(auto p : *this)
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
		out << *str;

		if(str+1 != t.end()) out << ",";
	}
	out << ")";
	return out;
}

ostream & operator<<(ostream &out, const Relation &r)
{
	return out << string(r);
}
