#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "Mimic.hpp"
#include "map.hpp"
#include "pair.hpp"

using namespace std;

Mimic::Mimic()
{
    srand(0);
}
Mimic::~Mimic(){}

//Part 1--------------------------------------------------------------
/**
 * createMap
 *
 * Creates a prefix-suffix map based on the input text.
 *
 * Go through the input text and examine each group of 3 words. Refer
 * to the first two words as the "prefix" and the third word as the
 * "suffix". Create a map that associates each prefix with each suffix.
 *  If you encounter a prefix that has been read already, add the new
 *  suffix to the list of suffixes already associated with that prefix;
 *  in this manner, each prefix can be associated with multiple
 *  suffixes and even multiple copies of the same suffix. Note that
 *  the input texts will only contain words separated by spaces.  Also
 *  note that the last two word prefix in the text should be associated
 *  with the suffix "THE_END".
 *
 * @param input
 * 		the sample text to be mimicked
 */
void Mimic::createMap(string input)
{
    istringstream sstr(input);

    string first, second, third;
    
    sstr >> first >> second >> third;
    
    // Empty out map in case it has something in it.
    _wordmap = ede::map();

    while (sstr.good())
    {
        stringstream tmpkey, tmpval;
        
        tmpkey << first << ' ' << second;
        
        if(third == "")
        {
            tmpval << "THE_END";
        }
        else
        {
            tmpval << third;
        }

        _wordmap.addKeyValPair(tmpkey.str(), tmpval.str());
        
        first = second;
        second = third;
        sstr >> third;

        // Do this once we have hit the end of the string.
        if(!sstr.good())
        {
            // Clear out the output streams
            tmpkey.str("");
            tmpval.str("");
           
            // Fill the output streams
            tmpkey << first << ' ' << second;
            tmpval << third;
            // Add the new data to the map
            _wordmap.addKeyValPair(tmpkey.str(), tmpval.str());

            // Set vars to their final values
            first = second;
            second = third;
            third = "THE_END";
            
            // Clear out the output streams
            tmpkey.str("");
            tmpval.str("");
            
            // Fill the output streams
            tmpkey << first << ' ' << second;
            tmpval << third;
            _wordmap.addKeyValPair(tmpkey.str(), tmpval.str());
        }
    }
}

/**
 * getSuffixList
 *
 * Returns the list of suffixes associated with the given prefix.
 * Returns an empty vector if the given prefix is not in the map or no
 * map has been created yet.
 *
 * @param prefix
 * 		the prefix to be found
 * @return a list of suffixes associated with the given prefix if the
 * 		prefix is found; an empty vector otherwise
 */
vector<string> Mimic::getSuffixList(string prefix)
{
    try
    {
        vector<string> retval = _wordmap[prefix];
        return retval;
    }
    // If the key does not exist, and return an empty vector.
    catch(out_of_range e)
    {
        return vector<string>();
    }
}

//Part 2--------------------------------------------------------------
/**
 * generateText
 *
 * Generates random text using the map created by the createMap method.
 *
 * To generate the new text, start with the first prefix that was read
 * and randomly select one of the suffixes associated with that prefix.
 * The next prefix is the second word from the previous prefix and the
 * selected suffix. Continue selecting random suffixes and building the
 * next prefix until the suffix "THE_END" is selected. The token
 * "THE_END" should not be returned as part of your generated text.
 *
 * @return random text generated using the map created with the sample
 * 		text; an empty string if no map has been created yet
 */
string Mimic::generateText()
{
    if(_wordmap.size() == 0)
        return string();
    // Temp code for debugging
    ostringstream retval;
    string first, second;

    ede::mapnode tmp = _wordmap[0];


    istringstream keyin(tmp.first);
    
    keyin >> first >> second;

    string newkey;

    while(second != "THE_END")
    {
        // update return value
        retval << first << " ";
       
        // Now do a bunch of crap to create a new key and get the next value
        ostringstream tmpkey;

        string tmpstr;

        tmpkey << first << " " << second;

        int index = rand() % _wordmap[tmpkey.str()].size();
        
        tmpstr = _wordmap[tmpkey.str()][index];

/*        
        retval << first << " " << second;

        if(tmpstr != "THE_END")
            {retval << " " << tmpstr << " ";}
*/
        first = second;
        second = tmpstr;
    }

    return retval.str();
}


