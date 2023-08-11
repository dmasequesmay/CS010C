#include <iostream>
#include <string>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {

    public:

        //Default constructor  
        Node();

        //Constructor
        Node(const string &, const int);

        //mutator function
        void SetLeftSub(Node*);

        //accessor function
        Node* GetLeftSub() const;

        //mutator function
        void SetRightSub(Node*);

        //accessor function
        Node* GetRightSub() const;

        //mutator function
        void SetStringNode(const string&);

        //accessor function
        string GetStringNode() const;

        //mutator function
        void SetCountNode(const int);

        //accessor function
        int GetCountNode() const;


    private:

        Node* leftSub;
        Node* rightSub;
        string stringNode;
        int countNode;

};

#endif