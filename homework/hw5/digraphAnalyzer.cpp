// digraphAnalyzer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "digraph.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::string;
using std::stoul;

/*
 * Calls the functions declared in digraph.h
 */
int main(int argc, char *argv[]) {
  if(argc != 3) {
    cerr << "Invalid arguments" << endl;
    exit(1);
  }

  // opens the input file
  ifstream inFile(argv[1]);

  // checks whether the input file was opened
  if(!inFile.is_open()) {
    cerr << "Failed to open input file." << endl;
    exit(1);
  }

  // reads the input file header and saves the digraph vector
  pair<int, vector<string>> inFileHeader = readInputFileHeader(inFile);
  vector<string> digraphVect = inFileHeader.second;

  // maps the words in the file to the digraphs in the vector
  map<string, vector<string>> wordMap = mapWords(digraphVect, inFile);

  // prints the map in order specified by command line parameter
  cout << wordMapToString(wordMap, *argv[2]);

  // queries the user
  cout << "q?>";
  string query;
  cin >> query;
  while (query.compare("quit") != 0) {
    // if input is a number, process the number,
    // otherwise process the string
    if(query.find_first_not_of("0123456789") == string::npos) {
      cout << processNum(stoul(query), wordMap);
    } else {
      cout << processString(query, wordMap);
    }
    cout << "q?>";
    cin >> query;
  }

  return 0;
}
