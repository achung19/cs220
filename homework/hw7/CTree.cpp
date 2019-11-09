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
  delete this->kids;
  delete this->sibs;
}

ostream& operator<<(ostream& os, CTree& rt) {
  return os << rt.toString();
}

CTree& CTree::operator^(CTree& rt) {
  this->addChild(&rt);
  return * this;
}

bool CTree::eq_Helper(const CTree * root1, const CTree * root2) {
  if(root1 == NULL && root2 == NULL) 
    return true;
  if(root1 != NULL && root2 != NULL)
    return root1->data == root2->data
      && eq_Helper(root1->sibs, root2->sibs)
      && eq_Helper(root1->kids, root2->kids);
  return false;
}

bool CTree::operator==(const CTree &root) {
  return eq_Helper(this, &root);
}

bool CTree::addSibling(char ch) {
  CTree * newNode = new CTree(ch);
  if(this->addSibling(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

bool CTree::addChild(char ch) {
  CTree * newNode = new CTree(ch);
  if(this->addChild(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

bool CTree::addSibling(CTree *root) {
  if(this->data == root->data || this->prev == NULL) {
    return false;
  }
  if(this->sibs == NULL) {
    this->sibs = root;
    root->prev = this;
    return true;
  }
  if(root->data < this->sibs->data) {
    root->sibs = this->sibs;
    this->sibs->prev = root;
    this->sibs = root;
    root->prev = this;
    return true;
  }
  return this->sibs->addSibling(root);
}

bool CTree::addChild(CTree *root) {
  if(root->prev != NULL || root->sibs != NULL) {
    return false;
  }
  if(this->kids == NULL) {
    this->kids = root;
    root->prev = this;
    return true;
  }
  if(root->data == this->kids->data) {
    return false;
  }
  if(root->data < this->kids->data) {
    root->sibs = this->kids;
    this->kids->prev = root;
    this->kids = root;
    root->prev = this;
    return true;
  }
  return this->kids->addSibling(root);
}

string CTree::toString() {
  stringstream stringbuilder;
  stringbuilder << this->data << endl;
  if(this->kids != NULL) {
    stringbuilder << this->kids->toString();
  }
  if(this->sibs != NULL) {
    stringbuilder << this->sibs->toString();
  }
  return stringbuilder.str();
}

