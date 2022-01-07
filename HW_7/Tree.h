#ifndef _TREE_H
#define _TREE_H

#include <cstdlib>
#include <string>

// tree of type T, can be used to implement a tree

template<typename T>
class Tree {
  friend class TTreeTest;
  
  T data;     // the value stored in the tree node

  Tree<T> * kids;  // children - pointer to first child of list, maintain order & uniqueness

  Tree<T> * sibs;  // siblings - pointer to rest of children list, maintain order & uniqueness
                 // this should always be null if the object is the root of a tree

  Tree<T> * prev;  // pointer to parent if this is a first child, or left sibling otherwise
                 // this should always be null if the object is the root of a tree

 public:
  
  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, Tree<U>& rt);
  Tree<T>(T pay);

  ~Tree<T>();  // clear siblings to right and children and this node
  
  Tree<T>& operator^(Tree<T>& rt);  //^ operator to do the same thing as addChild
  bool operator==(const Tree<T> &root); // return true if two Trees match node by node
  
  // siblings and children must be unique, return true if added, false otherwise
  bool addChild(T pay);

  // add tree root for better building, root should have null prev and sibs 
  // returns false on any type of failure, including invalid root
  bool addChild(Tree<T> *root);

  std::string toString(); // all T, separated by newlines, including at the end
  
 private:
  // these should only be called from addChild, and have the same restrictions
  // the root of a tree should never have any siblings
  // returns false on any type of failure, including invalid root
  bool addSibling(T pay);
  bool addSibling(Tree<T> *root);

};

#include "Tree.inc"
#endif
