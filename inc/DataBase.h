#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <ostream>

namespace DB
{

using namespace std;

typedef unordered_map<string, string> StrDict;
typedef unsigned long int Index;
typedef vector<Index> IndexList;

struct Scheme : public vector<string>
{
	string name;

	void join(const Scheme &other);
	Scheme operator+(const Scheme &other) const;
	Scheme& operator+=(const Scheme &other);
};

struct Tuple : public vector<string> {};
typedef set<Tuple> TupleSet;

class Relation
{
public:

public:
	Relation(const Scheme &s);
	Relation() = default;
	Relation(const Relation &other) = default;
	Relation(Relation &&other) = default;
	Relation& operator=(const Relation &other) = default;
	Relation& operator=(Relation &&other) = default;

	Relation select(Index index, string value) const;
	Relation select(Index index1, Index index2) const;
	Relation project(const IndexList &indices) const;
	Relation rename(StrDict mapping) const; // Renames the internal scheme
	Relation & rename_update(StrDict mapping); // Renames the internal scheme
	Relation rename(Scheme new_names) const; // Renames the internal scheme
	Relation & rename_update(Scheme new_names); // Renames the internal scheme
	Relation unioned(const Relation &other) const;
	Relation & union_update(const Relation &other);
	Relation join(const Relation &other) const;
	Relation & join_update(const Relation &other);
	Relation difference(const Relation &other) const;
	Relation & difference_update(const Relation &other);
	void insert(const Tuple &t);
	void insert(Tuple &&t);

	// getter functions
	const string & get_name() const { return scheme.name; }
	const Scheme & get_scheme() const { return scheme; }
	const TupleSet & get_tuples() const { return tuples; }
	size_t size() const { return tuples.size(); }

	// syntactic sugar
	Relation operator|(const Relation &other) const { return unioned(other); }
	Relation & operator|=(const Relation &other) { return union_update(other); }
	Relation operator+(const Relation &other) const { return join(other); }
	Relation & operator+=(const Relation &other) { return join_update(other); }
	Relation operator-(const Relation &other) const { return difference(other); }
	Relation & operator-=(const Relation &other) { return difference_update(other); }
	operator string() const;
private:
	Scheme scheme;
	TupleSet tuples;
};

class DataBase : public map<string, Relation>
{
public:
	Relation& operator[](string name);
	void insert(Relation r);
	bool has(string name) const;
	size_t db_size() const;
	explicit operator string() const;
};

} // end namespace DB

std::ostream & operator<<(std::ostream &out, const DB::Tuple &t);
std::ostream & operator<<(std::ostream &out, const DB::Scheme &s);
std::ostream & operator<<(std::ostream &out, const DB::Relation &r);

#endif // End include guard