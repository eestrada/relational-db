#include "DataBase.h"
#include "OrderedSet.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace DB;
using namespace std;

template <typename T, typename U>
ostream & operator<<(ostream &out, const pair<T,U> &p)
{
	out << "pair<\"" << p.first << "\", \"" << p.second << "\">";
	return out;
}

void Scheme::join(const Scheme &other)
{
	OrderedSet<string> selfset(*this);

	selfset += other;

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

	for(const auto &t : this->tuples)
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

	for(const auto &t : this->tuples)
	{
		if(t.at(index1) == t.at(index2)) r.insert(t);
	}
	
	return r;
}

ostream & operator<<(ostream &out, const IndexList &indices)
{
	out << "[ ";
	for(const auto &i : indices)
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

	for(const auto &i : indices)
	{
		tmp_sch.push_back(this->scheme.at(i));
	}

	Relation retval;
	retval.scheme = move(tmp_sch);

	if(indices.size() == 0)
	{
		retval.tuples = this->tuples;
		return retval;
	}

	for(const auto &t : this->tuples)
	{
		Tuple nt;
		for(const auto &i : indices)
		{
			nt.push_back(t.at(i));
		}

		if(nt.size() > 0) retval.insert(move(nt));
	}

	return retval;
}

Relation Relation::unioned(const Relation &other) const
{
	Relation retval = *this;
	return retval.union_update(other);
}

Relation & Relation::union_update(const Relation &other)
{
	if (&other == this) return *this; // unioning with self is a no-op

	IndexList pil;

	Index i1 = 0;
	for(auto &s1 : this->scheme)
	{
		Index i2 = 0;
		for(const auto &s2 : other.scheme)
		{
			if (s1 == s2) pil.push_back(i2);
			++i2;
		}
		++i1;
	}

	Relation fixed = other.project(pil);

	for (auto &t : fixed.tuples) { this->insert(t); }

	return *this;
}

Tuple join_tuple(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2)
{
	// Add all of t1 since we already know that all of it can be joined.
	Tuple retval = t1;

	// Add remaining values from t2 based on uniqueness of Scheme columns.
	auto size1 = s1.size();
	auto size2 = s2.size();
	for(auto i2 = 0; i2 < size2; ++i2)
	{
		bool unique = true;

		for(auto i1 = 0; i1 < size1; ++i1)
		{
			if(s2[i2] == s1[i1])
			{
				unique = false;
				break;
			}
		}
		if(unique) retval.push_back(t2[i2]);
	}

	return retval;
}

bool test_joinability(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2)
{
	// Check for joinability. Then append values from t1 that are either unique
	// based on the Scheme or match t2 based on the Scheme. If the Schemes
	// match columns, but the tuples do not match values, the tuples cannot be joined.
	auto size1 = s1.size();
	auto size2 = s2.size();
	for(auto i1 = 0; i1 < size1; ++i1)
	{
		for(auto i2 = 0; i2 < size2; ++i2)
		{
			if(s1[i1] == s2[i2] and t1[i1] != t2[i2]) return false;
		}
	}

	return true;
}

Relation Relation::join(const Relation &other) const
{
	if (&other == this) return *this; // joining with self is a no-op

	Scheme jscheme = this->scheme + other.scheme;

	Relation retval(jscheme);

	for(const auto &t1 : this->tuples)
	{
		for(const auto &t2 : other.tuples)
		{
			auto joinable = test_joinability(t1, t2, this->scheme, other.scheme);
			if(joinable)
			{
				Tuple t = join_tuple(t1, t2, this->scheme, other.scheme);
				retval.insert(move(t));
			}
		}
	}

	return retval;
}

Relation & Relation::join_update(const Relation &other)
{
	if (&other != this) *this = this->join(other);
	return *this;
}

Relation Relation::difference(const Relation &other) const
{
	Relation retval = *this;

	return retval.difference_update(other);
}

/*
Inplace difference operation.
*/
Relation & Relation::difference_update(const Relation &other)
{
	for(auto &t : other.tuples)
	{
		this->tuples.erase(t);
	}

	return *this;
}

void Relation::insert(const Tuple &t)
{
	tuples.insert(t);
}

void Relation::insert(Tuple &&t)
{
	tuples.insert(move(t));
}

Relation Relation::rename(StrDict mapping) const
{
	Relation retval = *this;
	return retval.rename_update(mapping);
}

Relation & Relation::rename_update(StrDict mapping)
{
	if(mapping.size() == 0) return *this;

	for(auto i = this->scheme.begin(); i != this->scheme.end(); ++i)
	{
		StrDict::mapped_type s;
		try { s = mapping.at(*i); }
		catch(const out_of_range &e) { continue; }
		/* else */
		*i = s;
	}

	return *this;
}

Relation Relation::rename(Scheme new_names) const
{
	Relation retval = *this;
	return retval.rename_update(new_names);
}

Relation & Relation::rename_update(Scheme new_names)
{
	if(new_names.size() != this->scheme.size())
		throw runtime_error("Scheme lengths do not match");

	this->scheme = move(new_names);

	return *this;
}

Relation::operator string() const
{
	const auto& sch = this->get_scheme();

	if(not sch.size()) return string();

	ostringstream out;
	for(const auto &t : this->get_tuples())
	{
		out << "  ";
		for(unsigned i = 0; i < sch.size(); ++i)
		{
			out << sch[i] <<"="<< t[i];

			if(i != sch.size()-1) out << " ";
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
    map<string, Relation>::insert({r.get_name(), move(r)});
}

bool DataBase::has(string name) const {	return this->count(name); }

size_t DataBase::db_size() const
{
	size_t retval = 0;
	for(auto &p : *this)
	{
		retval += p.second.get_tuples().size();
	}
	return retval;
}


DataBase::operator string() const
{
	ostringstream out;

	out << "Tables:\n";

	for(auto &p : *this)
	{
		out << "\t" << p.second.get_scheme() << "\n";


		for(auto &t : p.second.get_tuples())
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
