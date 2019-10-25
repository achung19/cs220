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

  ifstream inFile(argv[1]);

  if(!inFile.is_open()) {
    cerr << "Failed to open input file." << endl;
  }

  pair<int, vector<string>> inFileHeader = readInputFileHeader(inFile);
  vector<string> digraphVect = inFileHeader.second;

  map<string, vector<string>> wordMap = mapWords(digraphVect, inFile);

  cout << wordMapToString(wordMap, *argv[2]);

  cout << "q?>";
  string query;
  cin >> query;
  while (query.compare("quit") != 0) {
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
