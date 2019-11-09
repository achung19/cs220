#include "CTree.h"

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

CTree& CTree::operator^(CTree& rt) {

}

bool CTree::operator==(const CTree &root) {
  
}

bool CTree::addSibling(char ch) {
  if(this.sibs == NULL) {
    this.sibs = new CTree(ch);
    return true;
  }
  if(ch == this.sibs.data) {
    return false;
  }
  if(ch < this.sibs.data) {
    CTree newNode = new CTree(ch);

    newNode.sibs = this.sibs;
    this.sibs.prev = newNode;
    this.sibs = newNode;
    newNode.prev = this;
    return true;
  }
  return this.sibs.addSibling(ch);
}

bool CTree::addChild(char ch) {
  if(ch == this.data) {
    return false;
  }
  if(this.kids == NULL) {
    this.kids = CTree(ch);
    this.kids.prev = this;
    return true;
  }
  if(ch == this.kids.data) {
    return false;
  }
  if(ch < this.kids.data) {
    CTree newHead = new CTree(ch);
    
    newHead.sibs = this.kids;
    this.kids.prev = newHead;
    this.kids = newHead;
    newHead.prev = this;
    return true;
  }
  return this.kids.addSibling(ch);
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

string CTree::toString() {

}

