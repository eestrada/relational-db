#ifndef _PAIR_HPP_
#define _PAIR_HPP_

#include <stdexcept>
#include <algorithm>
#include <string>
#include "pair.hpp"

using namespace std;

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
        typename ede::map::iterator first, last, tmpiter;
        first = this->begin();
        last = this->end();

        mapnode tmp(key, strvec());

        tmpiter = find(first, last, tmp);
        
        if(tmpiter != last)
            return tmpiter->second;
        else
            throw out_of_range("The supplied key does not exist.");
    };

    bool addKeyValPair(const string &key, const string &val)
    {
        bool exists = false;
        try
        {
            strvec tmpsv = this->operator[](key);

            for(unsigned int i = 0; i < tmpsv.size(); ++i)
            {
                if(tmpsv[i] == val)
                {
                    exists = true;
                }
            }

            if(!exists)
            {
                tmpsv.push_back(val);
            }

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

}

#endif // define _PAIR_HPP_


