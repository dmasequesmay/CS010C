#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {

    public:

        AVLTree();

        ~AVLTree();

        void insert(const string &);

        int balanceFactor(Node*) const;

        void printBalanceFactors();

        void visualizeTree(const string &);

        void preOrder() const;

    private:

        Node* root;

        void destructor(Node*);

        void SetChild(Node* parent, string whichChild, Node* child);

        void ReplaceChild(Node* parent, Node* currentChild, Node* newChild);

        void rotate(Node*);

        void rotateLeft(Node*);

        void rotateRight(Node*);

        void printBalanceFactorsRecursive(Node*) const;

        void preOrderRecursive(Node *) const;

        /* Search for a string in the binary search tree. 
        It should return true if the string is in the tree, and false otherwise. 
         */
        bool search(const string &) const;

        bool search(Node* , const string &) const;

        Node* searchNode(Node* , const string &) const;

        /* Compute and return the height of a particular string in the tree. 
           The height of a leaf node is 0 (count the number of edges on the longest path). 
           Return -1 if the string does not exist. 
         */
        int height(Node*) const;

        void printBalanceFactors(Node*);

        void updateHeight(Node*);

};

#endif