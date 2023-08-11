
#include <iostream>
#include <string>

#include "Node.h"

using namespace std;

//Default Constructor initializes node with no children, string as empty string, and countNode as -1
Node::Node() {
    leftSub = nullptr;
    rightSub = nullptr;
    parent = nullptr;
    stringNode = "";
    count = -1;
}

//Constructor initializes node with no children, string as newString, and count as newCount
Node::Node(const string& newString, const int newCount) {
    leftSub = nullptr;
    rightSub = nullptr;
    parent = nullptr;
    stringNode = newString;
    count = newCount;
}

//returns true if node is a leaf (has no children), false otherwise
bool Node::isLeaf() const {
    return ((leftSub == nullptr) && (rightSub == nullptr));
}