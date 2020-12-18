/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */


    ifstream f(word_list_fname);
    string temp;
    if(f.is_open()) {
      while(getline(f, temp)) {
	if (temp.size() < 3)
	  continue;
	string temp1 = temp.substr(1, temp.size());
	string temp2 = temp;
	string temp3 = temp2.erase(1,1);
	if(d.homophones(temp, temp1) && d.homophones(temp, temp3))
	  ret.push_back(std::make_tuple(temp, temp1, temp3));
      }
    }

    return ret;
}
