#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <set>
#include <map>
#include <vector>
#include <string>
#include <ostream>

namespace DB
{

using namespace std;

typedef map<string, string> StrDict;
typedef long int Index;
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