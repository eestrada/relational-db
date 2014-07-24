#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <set>
#include <map>
#include <vector>
#include <string>
#include <ostream>


// TODO: make an ordered_set class that keeps track of the order  
// items were entered into the set. This is unlike the built in set
// since that is more along the lines of a sorted set. This class
// ought to simplify the process of doing joins and making sure that
// schemes do not have duplicate column entries.

namespace DB
{

using namespace std;

typedef map<string, string> StrDict;
typedef unsigned long int Index;
typedef vector<Index> IndexList;

struct Scheme : public vector<string>
{
	string name;
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

	//Relation select(StrDict query) const; // Select by multiple criteria at once
	Relation select(Index index, string value) const;
	Relation select(Index index1, Index index2) const;
	Relation project(const IndexList &indices) const;
	Relation rename(StrDict mapping) const; // Renames the internal scheme
	Relation unioned(const Relation &other) const;
	Relation join(const Relation &other) const;
	void insert(Tuple t);
	string get_name() const;
	Scheme get_scheme() const;
	TupleSet get_tuples() const;

	// Convenience functions
	Relation operator|(const Relation &other) { return unioned(other); }
	Relation operator+(const Relation &other) { return join(other); }
	operator string() const;
private:
	Scheme scheme;
	TupleSet tuples;
};

class DataBase
{
public:
	Relation& operator[](string name);
	void insert(Relation r);
	explicit operator string() const;
private:
	map<string, Relation> relations;
};

} // end namespace DB

std::ostream & operator<<(std::ostream &out, const DB::Tuple &t);
std::ostream & operator<<(std::ostream &out, const DB::Scheme &s);
std::ostream & operator<<(std::ostream &out, const DB::Relation &r);

#endif // End include guard