#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <stdexcept>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "pair.h"

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

typedef pair< string , vector<string> > mapnode;

class map : public vector < mapnode >
{

private:

public:

    vector<string> & operator[](const string &key)
    {
        int num = this->size();
        
        // Loop though the values of this until we find a key that matches
        for(int i = 0; i < num; ++i)
        {
            if(vector<mapnode>::operator[](i).first == key)
            {
                return vector<mapnode>::operator[](i).second;
            }
        }
        
        // If we have made it this far, then no value exists with this key
        // So throw an exception to indicate this.
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
            // If this key exists, then add this value to it
            vector<string> &tmpsv = this->operator[](key);
            
            tmpsv.push_back(val);

        }
        catch(out_of_range e)
        {
            //Otherwise, create a new key/value pair
            vector<string> tmpsv;
            tmpsv.push_back(val);
            mapnode tmpnode(key, tmpsv);

            this->push_back(tmpnode);
        }

        return exists;
    }
};

};

#endif // define _MAP_HPP_

