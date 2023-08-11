#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

private:
  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

  Node(): small(""), large(""), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr)
  {}

  Node(const string &title) : small(title), large(""), left(nullptr), 
                              middle(nullptr), right(nullptr), parent(nullptr)
  {}

  Node(const string &small, const string &large) : small(small), large(large), left(nullptr), 
                              middle(nullptr), right(nullptr), parent(nullptr)
  {}
  
  bool IsNodeFull();

  bool IsLeaf();

};

#endif