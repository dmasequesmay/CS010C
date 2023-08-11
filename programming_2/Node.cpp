#include <iostream>
#include <string>

#include "Node.h"

using namespace std;

//Default Constructor initializes node with no children, string as empty string, and countNode as -1
Node::Node() {
    leftSub = nullptr;
    rightSub = nullptr;
    stringNode = "";
    countNode = -1;
}

//Constructor initializes node with no children, string as newString, and count as newCount
Node::Node(const string& newString, const int newCount) {
    leftSub = nullptr;
    rightSub = nullptr;
    stringNode = newString;
    countNode = newCount;
}

//mutator function sets leftSub pointer
void Node::SetLeftSub(Node* leftSub) {
    this->leftSub = leftSub;
}

//accessor function returns leftSub pointer
Node* Node::GetLeftSub() const {
    return leftSub;
}

//mutator function sets rightSub pointer
void Node::SetRightSub(Node* rightSub) {
    this->rightSub = rightSub;
}

//accessor function returns rightSub pointer
Node* Node::GetRightSub() const {
    return rightSub;
}

//mutator function sets string of node
void Node::SetStringNode(const string& stringNode) {
    this->stringNode = stringNode;
}

//accessor function returns string of node
string Node::GetStringNode() const {
    return stringNode;
}

//mutator function sets count of node
void Node::SetCountNode(const int countNode) {
    this->countNode = countNode;
}

//accessor function returns count of node
int Node::GetCountNode() const {
    return countNode;
}