#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void insertRecursive(Node* , const string &);
  void SplitInsert(Node* , const string &);
  Node* GetParent(const string &);
  void preOrderRecursive(Node*) const;
  void inOrderRecursive(Node*) const;
  void postOrderRecursive(Node*) const;
  void removeRecursive(Node* , const string &);
  void SplitRemove(Node* , const string &);
  bool searchRecursive(Node* , const string &) const;
  void destructor(Node*);

};

#endif