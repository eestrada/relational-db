#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <stdexcept>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "pair.hpp"

using namespace std;

template < typename T >
ostream & operator<<(ostream &stream, const vector<T> &somevec)
{
    string delim = " ";

    for(unsigned int i = 0; i < somevec.size(); ++i)
    {
        stream << somevec[i];
        {
            stream << delim;
        }
    }

    return stream;
}


namespace ede
{

typedef vector<string> strvec;

typedef pair< string , strvec > mapnode;


class map : public vector < mapnode >
{

private:
    typedef typename ede::map::iterator myiter;

public:

    strvec & operator[](const string &key)
    {
        int num = this->size();

        for(int i = 0; i < num; ++i)
        {
            if(vector<mapnode>::operator[](i).first == key)
            {
                return vector<mapnode>::operator[](i).second;
            }
        }

        throw out_of_range("The supplied key does not exist.");
    };

    mapnode operator[](unsigned int index)
    {
        return vector<mapnode>::operator[](index);
    }

    bool addKeyValPair(const string &key, const string &val)
    {
        bool exists = false;
        try
        {
            strvec &tmpsv = this->operator[](key);
            
            tmpsv.push_back(val);

        }
        catch(out_of_range e)
        {
            strvec tmpsv;
            tmpsv.push_back(val);
            mapnode tmpnode(key, tmpsv);

            this->push_back(tmpnode);

        }

        return exists;
    }
};

};

#endif // define _MAP_HPP_

