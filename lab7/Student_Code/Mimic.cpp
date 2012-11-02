#include "Mimic.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "pair.hpp"

using namespace std;

Mimic::Mimic(){}
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

    string harold;

    vector<string> strvec;
   
    while (sstr.good())
    {
        string first, second, third;
        stringstream tmpkey, tmpval;
        sstr >> first >> second >> third;
        tmpkey << first << ' ' << second;
        if(third == "")
            tmpval << "THE_END";
        else
            tmpval << third;

        _wordmap.addKeyValPair(tmpkey.str(), tmpval.str());
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
        cout << "Caught out_of_range exception: " << e.what() << endl;
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
    return string();
}


