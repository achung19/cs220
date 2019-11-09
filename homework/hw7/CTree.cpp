#include <cstdlib>
#include <string>
#include <sstream>
#include "CTree.h"

using std::string;
using std::stringstream;
using std::endl;
using std::ostream;

CTree::CTree(char ch): data(ch), kids(NULL), sibs(NULL), prev(NULL) {}

CTree::~CTree() {
  if (this == NULL) {
    exit(1); 
  }
  if (this.sibs != NULL) {
    this.sibs.~CTree();
  }
  if (this.kids != NULL) {
    this.kids.~CTree();
  }
  free(this);
}

friend ostream& operator<<(ostream& os, CTree& rt) {
  os << rt.toString();
}

CTree& CTree::operator^(CTree& rt) {
  this.addChild(rt);
  return this;
}

bool CTree::operator==(const CTree &root) {
  if(this.data != root.data) {
    return false;
  }
  if(this.sibs == NULL || root.sibs == NULL) {
    if(this.sibs != NULL || root.sibs != NULL) {
      return false;
    } else {
      return true;
    }
  }
  if(this.kids == NULL || root.kids == NULL) {
    if(this.kids != NULL || root.kids != NULL) {
      return false;
    } else {
      return true;
    }
  }
  return this.sibs == root.sibs && this.kids == root.kids;
}

bool CTree::addSibling(char ch) {
  CTree newNode = new CTree(ch);
  if(this.addSibling(newNode) == false) {
    free(newNode);
    return false;
  }
  return true;
}

bool CTree::addChild(char ch) {
  CTree newNode = new CTree(ch);
  if(this.addChild(newNode) == false) {
    free(newNode);
    return false;
  }
  return true;
}

bool CTree::addSibling(CTree *root) {
  if(this.sibs == NULL) {
    this.sibs = root;
    root.prev = this;
    return true;
  }
  if(root.data == this.sibs.data) {
    return false;
  }
  if(root.data < this.sibs.data) {
    root.sibs = this.sibs;
    this.sibs.prev = root;
    this.sibs = root;
    root.prev = this;
    return true;
  }
  return this.sibs.addSibling(root);
}

bool CTree::addChild(CTree *root) {
  if(root.prev != NULL || root.sibs != NULL || root.data == this.data) {
    return false;
  }
  if(this.kids == NULL) {
    this.kids = root;
    root.prev = this;
    return true;
  }
  if(root.data == this.kids.data) {
    return false;
  }
  if(root.data < this.kids.data) {
    root.sibs = this.kids;
    this.kids.prev = root;
    this.kids = root;
    root.prev = this;
    return true;
  }
  return this.kids.addSibling(root);
}

string CTree::toString() {
  stringstream stringbuilder;
  stringbuilder << this.data << endl;
  if(this.kids != NULL) {
    stringbuilder << this.kids.toString();
  }
  if(this.siblings != NULL) {
    stringbuilder << this.sibs.toString();
  }
  return stringbuilder.str();
}

