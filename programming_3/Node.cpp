#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

//if node is full, small and large are not empty
bool Node::IsNodeFull() {
    return ((!large.empty()) && (!small.empty()));
}

//if node is a leaf, left, middle, and right pointers are all nullptr
bool Node::IsLeaf() {
    return (left == nullptr) && (middle == nullptr) && (right == nullptr);
}