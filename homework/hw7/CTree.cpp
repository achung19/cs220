#include <cstdlib>
#include <string>
#include <sstream>
#include "CTree.h"

using std::string;
using std::stringstream;
using std::endl;
using std::ostream;

/*
 * CTree constructor.
 * 
 * data: data of current node
 * kids: kids below the node
 * sibs: sib to the right of the node
 * prev: the node before it (prev sib or parent)
 */
CTree::CTree(char ch): data(ch), kids(NULL), sibs(NULL), prev(NULL) {}

/*
 * CTree descructor.
 */
CTree::~CTree() {
  delete this->kids;
  delete this->sibs;
}

/*
 * Output insert operator.
 */
ostream& operator<<(ostream& os, CTree& rt) {
  return os << rt.toString();
}

/*
 * Add child operator.
 */
CTree& CTree::operator^(CTree& rt) {
  this->addChild(&rt);
  return * this;
}

/*
 * Helper for equality operator, takes in two roots and recursively
 * checks for equality.
 */
bool CTree::eq_Helper(const CTree * root1, const CTree * root2) {
  if(root1 == NULL && root2 == NULL) 
    return true;
  if(root1 != NULL && root2 != NULL)
    return root1->data == root2->data
      && eq_Helper(root1->sibs, root2->sibs)
      && eq_Helper(root1->kids, root2->kids);
  return false;
}

/*
 * Equality operator.
 */
bool CTree::operator==(const CTree &root) {
  return eq_Helper(this, &root);
}

/*
 * Creates a new node and adds it as a sibling in order from the
 * this pointer.
 *
 * Parameters:
 * ch - value of the new node
 */
bool CTree::addSibling(char ch) {
  CTree * newNode = new CTree(ch);
  if(this->addSibling(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

/*
 * Creates a new node and adds it as a child to the this pointer,
 * adds the child as a sibling to this's kids pointer.
 *
 * Parameters:
 * ch - value of new node
 */
bool CTree::addChild(char ch) {
  CTree * newNode = new CTree(ch);
  if(this->addChild(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

/*
 * Same as addSibling(char) but with an existing root node.
 *
 * Parameters:
 * root - pointer to the root node
 */
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

/*
 * Same as addChild(char) but with an existing root node.
 *
 * Parameters:
 * root - pointer to the root node.
 */
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

/*
 * Returns a string version of the this tree, traversing
 * in DFS order.
 */
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

