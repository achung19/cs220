// digraph.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using std::ifstream;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;

/*
 *
 */
pair<int, vector<string>> readInputFile(ifstream inFile) {
  int numDigraphs;
  vector<string> digraphVect;

  // extract number of digraphs
  inFile >> numDigraphs;

  // place each digraph in a digraph vector
  for(int i = 0; i < numDigraphs; i++) {
    string name;
    inFile >> name;
    digraphVect.push_back(name);
  }

  return make_pair(numDigraphs, digraphVect);
}

/*
 *
 */
map<string, vector<string>> mapWords(vector<string> digraphVect,
				     ifstream inFile) {
  map<string, vector<string>> wordMap;

  // create an empty vector for each digraph in the map
  for(vector<string>::iterator iter = digraphVect.begin();
      iter != digraphVect.end();
      iter++) {
    if(wordMap.find(*iter) != wordMap.end()) {
      wordMap[*iter] =  vector<string> v;
    }
  }

  // extract each word from the input file
  string temp;
  while(inFile >> temp) {
    // check for each digraph in that word
    for(vector<string>::iterator iter = digraphVect.begin();
	iter != digraphVect.end();
	iter++) {
      // if the word contains a digraph, push the word
      // onto the corresponding digraph vector in the map
      if(temp.find(*iter) != string::npos) {
	wordMap[*iter].push_back(temp);
      }   
    }
  }

  return wordMap;
}

string stringVectorToString(vector<string> stringVect) {
  
}
