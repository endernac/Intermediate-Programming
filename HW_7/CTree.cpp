#include "CTree.h"
#include <cstdlib>
#include <string>
#include <iostream>

std::ostream& operator<<(std::ostream& os, CTree& rt) {
  return os << rt.toString();
}

CTree::CTree(char ch): data(ch), kids(nullptr), sibs(nullptr), prev(nullptr) {} 

CTree::~CTree() {
  if(kids) {
    delete kids;
    kids = nullptr;
  }
  if(sibs) {
    delete sibs;
    sibs = nullptr;
  }
}
  
CTree& CTree::operator^(CTree& rt) {
  addChild(&rt);
  return *this;
}

bool CTree::operator==(const CTree &root) {
  bool d = true;
  bool k = true;
  bool s = true;

  d = d && (this->data == root.data);

  if(this->kids && root.kids) {
    // if they both have kids repeat the algorith for the kids
    k = (this->kids == root.kids);
  } else if(this->kids != root.kids) {
    // if only one of them has kids they aren't equal
    k = false;
  }

  if(this->sibs && root.sibs) {
    // if they both have siblings repeat the algorith for the kids
    s = (this->sibs == root.sibs);
  } else if(this->sibs != root.sibs) {
    // if only one of them has kids they aren't equal
    s = false;
  }

  return d + k + s;
  // make sure the data in the node and all the right descendents match
} 
  
bool CTree::addChild(char ch) { 
  //create tree node to hold the new character
    CTree* new_node = new CTree(ch);
    if (!new_node) {  //allocation failed!
      return false;
    }

  if(!(addChild(new_node))) {
    delete new_node;
    return false;
  }

  // addition was successful
  return true;
}

bool CTree::addChild(CTree *root) {
  // 'root' is has siblings/parent or is an ancestor of 'this' (i.e. not a valid root)
  CTree* insert = root;
  if(insert->sibs || insert->prev) {
    return false;
  }

  CTree* cur = this;
  while (cur) {
    if (insert == cur) {
      return false;
    }
    cur = cur->prev;
  }

  // 'this' does not have any kids yet (assumption 1 of addSibling)
  if(!kids || root->data < kids->data) {
    if(kids) {
      root->sibs = kids;
      kids->prev = root;
    }
    
    this->kids = root;
    root->prev = this;
    return true;
  }
  
  // Call addSibling on the child of the node since it exists
  // the child will definitely be the first sibling (assumption 2)
  // try to add new node as a sibling. If it fails, delete the node
  if(!(this->kids->addSibling(root))) {
    return false;
  }
  
  // addition was successful
  return true;
}

std::string CTree::toString() {
  std::string k("");
  std::string s("");
  std::string d("");

  d += data;
  d += "\n";

  if(kids) {
    k += kids->toString();
  }
  if(sibs) {
    s += sibs->toString();
  }

  return d + k + s;

}

std::string CTree::pp() {
  std::string k("");
  std::string s("");
  std::string d("");

  d += data;

  if(kids) {
    k += "\n";
    k += kids->pp();
  }
  if(sibs) {
    s += sibs->pp();
  }

  return d + s  + k;

}


bool CTree::addSibling(char ch) {
  // Assumption 1: 'this' exists (checked in addChild)
  // Assumption 2: 'this' is the first sibling (checked in addChild)

  //create tree node to hold the new character
  CTree* new_node = new CTree(ch);
  if (!new_node) {  //allocation failed!
    return false;
  }

  // try to add new node as a sibling. If it fails, delete the node
  if(!addSibling(new_node)) {
    delete new_node;
    return false;
  }

  // addition was successful
  return true;
}

bool CTree::addSibling(CTree *root) {
  // Assumption 1: 'this' exists (checked in addChild)
  // Assumption 2: 'this' is the first sibling (checked in addChild)
  // Assumption 3: 'root' has a value in data

  // 'root' is has siblings/parent or is an ancestor of 'this' (i.e. not a valid root)
  CTree* insert = root;
  if(insert->sibs || insert->prev) {
    return false;
  }

  CTree* cur = this;
  while (cur) {
    if (insert == cur) {
      return false;
    }
    cur = cur->prev;
  }

  // 'this' already has a sibling with the 'root' data value
  cur = this;
  while (cur) {
    if (cur->data == root->data) {
      return false;
    }
    cur = cur->sibs;
  }

  // 'this' is a root
  cur = this;
  if(!this->prev) {
    return false;
  }

  // loop until you reach the end of sibs or reach the last val that's less than the array
  cur = this;
  while (cur->sibs && (cur->sibs->data < root->data)) {
    cur = cur->sibs;
  }

  root->sibs = cur->sibs; // set the sibling of 'root' to the sibling of 'this'
  cur->sibs = root; // set sibling of 'this' to 'root'
  root->prev = cur; // set prev of 'root' to 'this'
  return true;  
}
