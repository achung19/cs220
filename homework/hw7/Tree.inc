#include <cstdlib>
#include <string>
#include <sstream>

// adding comments here is ugly

/*
 * Constructor for tree with generic values.
 */
template<typename T>
Tree<T>::Tree(T ch): data(ch), kids(NULL), sibs(NULL), prev(NULL) {}

/*
 * Destructor.
 */
template<typename T>
Tree<T>::~Tree<T>() {
  delete this->kids;
  delete this->sibs;
}

/*
 * Same operators as CTree.
 */
template<typename E>
std::ostream& operator<<(std::ostream& os, Tree<E>& rt) {
  return os << rt.toString();
}

template<typename T>
Tree<T>& Tree<T>::operator^(Tree<T>& rt) {
  this->addChild(&rt);
  return * this;
}

/*
 * Generic equality operator helper.
 */
template<typename T>
bool Tree<T>::eq_Helper(const Tree<T> * root1, const Tree<T> * root2) {
  if(root1 == NULL && root2 == NULL) 
    return true;
  if(root1 != NULL && root2 != NULL)
    return root1->data == root2->data
      && eq_Helper(root1->sibs, root2->sibs)
      && eq_Helper(root1->kids, root2->kids);
  return false;
}

template<typename T>
bool Tree<T>::operator==(const Tree<T> &root) {
  return eq_Helper(this, &root);
}

/*
 * Same functions as CTree.
 */
template<typename T>
bool Tree<T>::addSibling(T ch) {
  Tree<T> * newNode = new Tree<T>(ch);
  if(this->addSibling(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

template<typename T>
bool Tree<T>::addChild(T ch) {
  Tree<T> * newNode = new Tree<T>(ch);
  if(this->addChild(newNode) == false) {
    delete newNode;
    return false;
  }
  return true;
}

template<typename T>
bool Tree<T>::addSibling(Tree<T> *root) {
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

template<typename T>
bool Tree<T>::addChild(Tree<T> *root) {
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
 * No changes.
 */
template<typename T>
std::string Tree<T>::toString() {
  std::stringstream stringbuilder;
  stringbuilder << this->data << std::endl;
  if(this->kids != NULL) {
    stringbuilder << this->kids->toString();
  }
  if(this->sibs != NULL) {
    stringbuilder << this->sibs->toString();
  }
  return stringbuilder.str();
}

