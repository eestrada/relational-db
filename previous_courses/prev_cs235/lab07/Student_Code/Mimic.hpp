#ifndef _MIMIC_HPP_
#define _MIMIC_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "MimicInterface.h"
#include "map.hpp"

class Mimic : public MimicInterface
{
    private:
        ede::map _wordmap;

	public:
		Mimic();
		virtual ~Mimic();

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
		virtual void createMap(std::string input);

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
		virtual std::vector<std::string> getSuffixList(std::string prefix);

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
		virtual std::string generateText();
};

#endif // define _MIMIC_HPP_

