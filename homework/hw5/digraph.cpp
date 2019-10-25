// digraph.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cctype>
#include "digraph.h"

using std::string;
using std::ifstream;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::stringstream;
using std::endl;
using std::cerr;
using std::transform;
using std::cout;

/*
 *
 */
pair<int, vector<string>> readInputFileHeader(ifstream &inFile) {
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
				     ifstream &inFile) {
  // initialize the map to contain empty vectors for every digraph
  map<string, vector<string>> wordMap;
  for(vector<string>::iterator iter = digraphVect.begin();
      iter != digraphVect.end();
      iter++) {
    wordMap[*iter];
  }
    
  // extract each word from the input file
  string nextWord;
  while(inFile >> nextWord) {
    // remove punctuation
    if(nextWord.find(',') != string::npos) { 
      nextWord.replace(nextWord.find(','), nextWord.find(',')+1, "");
    }
    if(nextWord.find('.') != string::npos) { 
      nextWord.replace(nextWord.find('.'), nextWord.find('.')+1, "");
    }
    if(nextWord.find('?') != string::npos) { 
      nextWord.replace(nextWord.find('?'), nextWord.find('?')+1, "");
    }
    if(nextWord.find('!') != string::npos) { 
      nextWord.replace(nextWord.find('!'), nextWord.find('!')+1, "");
    }
    // convert lowercase and put into nextWord using lambda func
    transform(nextWord.begin(), nextWord.end(), nextWord.begin(),
	      [](unsigned char c) { return std::tolower(c); });
    
    // check for each digraph in that word
    for(vector<string>::iterator iter = digraphVect.begin();
	iter != digraphVect.end();
	iter++) {
      // if the word contains a digraph, push the word
      // onto the corresponding digraph vector in the map
      if(nextWord.find(*iter) != string::npos) {
	wordMap[*iter].push_back(nextWord);
      }
    }
  }

  return wordMap;
}

string wordMapToString(map<string, vector<string>> wordMap, char c) {
  stringstream stringbuilder;

  if(c == 'a') {
    // for each digraph in map
    for(map<string, vector<string>>::iterator mapIter = wordMap.begin();
	mapIter != wordMap.end();
	mapIter++) {
      // print the digraph
      stringbuilder << mapIter->first << ": [";

      // for each word matching the digraph
      bool first = true; 
      for(vector<string>::iterator vectIter = mapIter->second.begin();
	  vectIter != mapIter->second.end();
	  vectIter++) {
	// print the word
	if(first) {
	  stringbuilder << *vectIter;
	  first = false;
	} else {
	  stringbuilder << ", " << *vectIter;
	}
      }
      
      stringbuilder << "]" << endl;
    }
  } else if(c == 'r') {
    // for each digraph in map
    for(map<string, vector<string>>::reverse_iterator mapIter =
	  wordMap.rbegin();
	mapIter != wordMap.rend();
	mapIter++) {
      // print the digraph
      stringbuilder << mapIter->first << ": [";

      // for each word matching the digraph
      bool first = true;
      for(vector<string>::iterator vectIter = mapIter->second.begin();
	  vectIter != mapIter->second.end();
	  vectIter++) {
	// print the word
	if(first) {
	  stringbuilder << *vectIter;
	    first = false;
	} else {
	  stringbuilder << ", " << *vectIter;
	}
      }
      
      stringbuilder << "]" << endl;
    }
  } else if(c == 'c') {
    // reverse the map keys and values, replacing the vector with its size
    map<int, string> reversedMap;
    for(map<string, vector<string>>::iterator revIter = wordMap.begin();
	revIter != wordMap.end();
	revIter++) {
      reversedMap[revIter->second.size()] = revIter->first;
    }
    
    // for each digraph in map (in count order)
    for(map<int, string>::reverse_iterator mapIter = reversedMap.rbegin();
	mapIter != reversedMap.rend();
	mapIter++) {
      // print the digraph
      stringbuilder << mapIter->second << ": [";

      // find the map pair in the original map
      map<string, vector<string>>::iterator digraphIter =
	wordMap.find(mapIter->second);
      
      // for each word matching the digraph
      bool first = true;
      for(vector<string>::iterator vectIter = digraphIter->second.begin();
	  vectIter != digraphIter->second.end();
	  vectIter++) {
	// print the word
	if(first) {
	  stringbuilder << *vectIter;
	  first = false;
	} else {
	  stringbuilder << ", " << *vectIter;
	} 
      }
      
      stringbuilder << "]" << endl;
    }
  } else {
    cerr << "Order must be 'a', 'r', or 'c'." << endl;
  }

  return stringbuilder.str();
}
