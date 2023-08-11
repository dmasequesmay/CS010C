#include <iostream>
#include <string>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {

    public:
        
        //AVLTree class has access to public and private variables
        friend class AVLTree;

        //Default constructor  
        Node();

        //Constructor
        Node(const string &, const int);

        //accessor function
        bool isLeaf() const;



    private:

        Node* leftSub;
        Node* rightSub;
        Node* parent;
        string stringNode;
        int count;
        int height;

};

#endif