// digraph.h

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

/*
 *
 */
std::pair<int, std::vector<std::string> > readInputFileHeader(std::ifstream&);

/*
 *
 */
std::map<std::string, std::vector<std::string> > mapWords(std::vector<std::string>, std::ifstream&);

/*
 *
 */
std::string wordMapToString(std::map<std::string, std::vector<std::string> >, char);

/*
 *
 */
std::string processNum(unsigned int, std::map<std::string, std::vector<std::string>>);

/*
 *
 */
std::string processString(std::string, std::map<std::string, std::vector<std::string>>);
