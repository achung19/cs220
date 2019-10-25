// digraphAnalyzer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "digraph.h"

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::string;

/*
 * Calls the functions declared in digraph.h
 */
int main(int argc, char *argv[]) {
  if(argc != 3) {
    cerr << "Usage: .//digraphAnalyzer input.txt order" << endl;
    exit(1);
  }

  ifstream inFile(argv[1]);

  if(!inFile.is_open()) {
    cerr << "Failed to open input file." << endl;
  }

  pair<int, vector<string>> inFileHeader = readInputFileHeader(inFile);
  // int numDigraphs = inFileHeader.first;
  vector<string> digraphVect = inFileHeader.second;

  map<string, vector<string>> wordMap = mapWords(digraphVect, inFile);

  cout << wordMapToString(wordMap, *argv[2]);
  
  return 0;
}
