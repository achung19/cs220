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
 * Maps the digraphs to a vector of words in the text file
 *
 * Parameters:
 * digraphVect: a vector of digraphs to map
 * inFile: an input file pointing to the start of the texts
 *
 * Returns:
 * a map from a digraph to a vector of words that contain the digraph
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
    // convert lowercase using lambda func
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

/*
 * Converts a map of digraphs and words to a string
 *
 * Parameters:
 * wordMap: a map to convert to a string
 * c: a character of either a, r,, or c denoting the order
 * of iteration
 * a for ASCII order, r for reverse ASCII order, c for count order
 */
string wordMapToString(map<string, vector<string>> wordMap, char c) {
  stringstream stringbuilder;

  if(c == 'a') {
    // for each digraph in map (iterate thru ASCII order)
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
    // for each digraph in map (iterate thru reverse ASCII order)
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
    // create a new vector of pairs containing the digraph
    // and associated words
    vector<pair<string, vector<string>>> pairVect;
    for(map<string, vector<string>>::iterator pairIter = wordMap.begin();
	pairIter != wordMap.end();
	pairIter++) {
      pairVect.push_back(make_pair(pairIter->first, pairIter->second));
    }

    // sort the vector by word vector size
    // from largest to smallest size
    sort(pairVect.begin(), pairVect.end(),
	 [](pair<string, vector<string>> p1,
	    pair<string, vector<string>> p2)
	 { return (p1.second.size() > p2.second.size()); });
	 
    // for each digraph in map (in count order)
    for(vector<pair<string, vector<string>>>::iterator mapIter =
	  pairVect.begin();
	mapIter != pairVect.end();
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
  } else {
    cerr << "Invalid arguments" << endl;
    exit(1);
  }

  return stringbuilder.str();
}

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
string processNum(unsigned int numDigraphs,
		  map<string, vector<string>> wordMap) {
  stringstream stringbuilder;
  bool isNone = true;
  
  for(map<string, vector<string>>::iterator mapIter = wordMap.begin();
      mapIter != wordMap.end();
      mapIter++) {
    if(mapIter->second.size() == numDigraphs) {
      isNone = false;
      stringbuilder << mapIter->first << endl;
      for(vector<string>::iterator vectIter = mapIter->second.begin();
	  vectIter != mapIter->second.end();
	  vectIter++) {
	stringbuilder << *vectIter << endl;
      }
    }
  }
  if(isNone) return "None\n";
  return stringbuilder.str();
}

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
string processString(string digraph, map<string, vector<string>> wordMap) {
  // convert lowercase using lambda func
  transform(digraph.begin(), digraph.end(), digraph.begin(),
	    [](unsigned char c) { return std::tolower(c); });

  stringstream stringbuilder;
  
  map<string, vector<string>>::iterator itFinder = wordMap.find(digraph);
  if(itFinder == wordMap.end()) {
    return "No such digraph\n";
  }

  stringbuilder << itFinder->second.size() << endl;

  for(vector<string>::iterator vectIter = itFinder->second.begin();
      vectIter != itFinder->second.end();
      vectIter++) {
    stringbuilder << *vectIter << endl;
  }

  return stringbuilder.str();
}
