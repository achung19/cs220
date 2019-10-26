// digraph.h

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

/*
 * Reads the input file header
 *
 * Parameters:
 * inFile: input file pointer pointing to start of
 * file to read from
 *
 * Returns:
 * an int representing the number of digraphs
 * a vector of the digraphs
 */
std::pair<int, std::vector<std::string> > readInputFileHeader(std::ifstream&);

/*
 * Maps the digraphs to a vector of words in the text file
 *
 * Parameters:
 * digraphVect: a vector of digraphs to map
 * inFile: an input file pointing to the start of the texts
 *
 * Returns:
 * a map from a digraph to a vector of words that contain the digraph
 */
std::map<std::string, std::vector<std::string> > mapWords(std::vector<std::string>, std::ifstream&);

/*
 * Converts a map of digraphs and words to a string
 *
 * Parameters:
 * wordMap: a map to convert to a string
 * c: a character of either a, r,, or c denoting the order
 * of iteration
 * a for ASCII order, r for reverse ASCII order, c for count order
 */
std::string wordMapToString(std::map<std::string, std::vector<std::string> >, char);

/*
 * Takes in a number and a map from digraphs to word vectors and outputs
 * every digraph that has the specified number of associated words along
 * with those associated words
 *
 * Parameters:
 * numDigraphs: number of words to look for for each digraph
 * wordMap: map from digraphs to list of words
 *
 * Returns:
 * string of a digraph and its associated words
 */
std::string processNum(unsigned int, std::map<std::string, std::vector<std::string>>);

/*
 * Takes in a digraph and a map from digraphs to word vectors and outputs
 * the number of associated words and said associated words
 *
 * Parameters:
 * digraph: the digraph to look for
 * wordMap: map from digraphs to list of words
 *
 * Returns:
 * string of the number of digraph's associated words and associated words
 */
std::string processString(std::string, std::map<std::string, std::vector<std::string>>);
