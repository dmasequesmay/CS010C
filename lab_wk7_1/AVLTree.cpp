#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}
//destructor calls helper function to delete nodes recursively
AVLTree::~AVLTree() {
    destructor(root);
}

//passes in node to delete and traverses through tree to delete nodes recursively
void AVLTree::destructor(Node* target) {
    //base case: return if target does not exist
    if (target == nullptr) {
        return;
    }
    //delete starting from left subtree, middle subtree, then right subtree. Finally, delete root at the end
    destructor(target->leftSub);
    destructor(target->rightSub);
    delete target;
}

void AVLTree::insert(const string &newString) {
    //if node with newString already exists, increment count by 1
    if (search(newString)) {
        Node* target = searchNode(root, newString);
        target->count = target->count + 1;
        return;
    }
    //if node with Newstring does not already exist in tree, 
    //create new node initializing stringNode with newString and count with 1
    Node* newNode = new Node(newString, 1);
    //if tree is empty, initialize root with newNode
    if (root == nullptr) {
        root = newNode;
        root->parent = nullptr;
    }
    else {
        //if tree is not empty, traverse tree to find correct place to insert
        //while loop starts at root
        Node* currNode = root;
        while (currNode != nullptr) {
            //currNode moves to left subtree if newNode string is less than currNode string
            if (newNode->stringNode < currNode->stringNode) {
                //if there is no left subtree, insert newNode
                if (currNode->leftSub == nullptr) {
                    currNode->leftSub = newNode;
                    newNode->parent = currNode;
                    currNode = nullptr;
                }
                //keep going down the left subtree
                else {
                    currNode = currNode->leftSub;
                }
            }
            //currNode moves to right subtree if newNode string is greater than currNode string
            else {
                //if there is no right subtree, insert newNode
                if (currNode->rightSub == nullptr) {
                    currNode->rightSub = newNode;
                    newNode->parent = currNode;
                    currNode = nullptr;
                }
                //keep going down the right subtree
                else {
                    currNode = currNode->rightSub;
                }
            }
        }
    }

    //start from leaf of tree where newNode was inserted and traverse up tree to check balance factors of each node
    newNode = newNode->parent;
    while (newNode != nullptr) {
        //call rotate to update balance factors. if unbalanced, rotate left/right
        rotate(newNode);
        newNode = newNode->parent;
    }
}

//update height and rotate if balance factors are not 0, -1, 1
void AVLTree::rotate(Node* target) {
    updateHeight(target);
    //unbalanced to the right, must rotate left
    if (balanceFactor(target) == -2) {
        //double rotation rotates right first and then rotates left
        if (balanceFactor(target->rightSub) == 1) {
            rotateRight(target->rightSub);
        }
        rotateLeft(target);
    }
    //unbalanced to the left, must rotate right
    else if (balanceFactor(target) == 2) {
        //double rotation rotates left first and then rotates right
        if (balanceFactor(target->leftSub) == -1) {
            rotateLeft(target->leftSub);
        }
        rotateRight(target);
    }
}

//at node passed in, rotate to the left
void AVLTree::rotateLeft(Node* target) {
    //left sub of target's right sub
    Node* rightLeftChild = (target->rightSub)->leftSub;
    //if target is not root, replace target with target's right sub
    if (target->parent != nullptr) {
        ReplaceChild(target->parent, target, target->rightSub);
    }
    //if target is root, replace root with target's right sub and update the root's parent
    else {
        root = target->rightSub;
        root->parent = nullptr;
    }
    //assign target to target's right sub's left sub
    SetChild(target->rightSub, "left", target);
    //assign rightLeftChild to target's right sub
    SetChild(target, "right", rightLeftChild);
}

//at node passed in, rotate to the right
void AVLTree::rotateRight(Node* target) {
    //right subh of target's left sub
    Node* leftRightChild = (target->leftSub)->rightSub;
    //if target is not root, replace target with target's left sub
    if (target->parent != nullptr) {
        ReplaceChild(target->parent, target, target->leftSub);
    }
    //if target is root, replace with target's left sub and update the root's parent
    else {
        root = target->leftSub;
        root->parent = nullptr;
    }
    //assign target to target's right sub's left sub
    SetChild(target->leftSub, "right", target);
    //assign leftRightChild to target's left sub
    SetChild(target, "left", leftRightChild);
}

//assign a child to a parent's left or right sub
void AVLTree::SetChild(Node* parent, string whichChild, Node* child) {
    //must assign to left or right child, return if unclear
    if ((whichChild != "left") && (whichChild != "right")) {
        return;
    }
    //assign parent's left sub to child
    if (whichChild == "left") {
        parent->leftSub = child;
    }
    //assign parent's right sub to child
    else {
        parent->rightSub = child;
    }
    //if child is a node containing data, update parent 
    if (child != nullptr) {
        child->parent = parent;
    }
    //update height of parent
    updateHeight(parent);
}

//replace a currentChild with a newChild
void AVLTree::ReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
    //if currentChild is parent's leftSub, assign newChild to parent's leftSub
    if (parent->leftSub == currentChild) {
        SetChild(parent, "left", newChild);
    }
    //if currentChild is parent's rightSub, assign newChild to parent's rightSub
    else if (parent->rightSub == currentChild) {
        SetChild(parent, "right", newChild);
    }
}

//update the height of node
void AVLTree::updateHeight(Node* target) {
    //if node is a leaf (has no children), height is -1
    int left = -1;
    int right = -1;

    //if target has left child, get left child's height
    if (target->leftSub != nullptr) {
        left = target->leftSub->height;
    }
    //if target has right child, get right child's height
    if (target->rightSub != nullptr) {
        right = target->rightSub->height;
    }
    //assign height with the greater value + 1
    if (left > right) {
        target->height = left + 1;
    }
    else {
        target->height = right + 1;
    }
}

//return the value of a node's balance factor
int AVLTree::balanceFactor(Node* target) const {
    //if leftSub or rightSub are leaves(has no children), height is -1
    int leftHeight = -1;
    int rightHeight = -1;

    //if target has left child, get left child's height
    if (target->leftSub != nullptr) { 
        leftHeight = target->leftSub->height; 
    }
    //if target has right child, get right child's height
    if(target->rightSub != nullptr) { 
        rightHeight = target->rightSub->height; 
    }
    //return balance factor (left child's height = right child's height)
    return (leftHeight - rightHeight); 
}

//start from root and traverse down tree in order, printing balance factors of each node
void AVLTree::printBalanceFactors() {
    printBalanceFactorsRecursive(root);
    cout << endl;
}

//recursie function that traverses down left subtree, printing balance factor of node, and traversing down right subtree
void AVLTree::printBalanceFactorsRecursive(Node* target) const {
    if (target == nullptr) {
        return;
    }
    printBalanceFactorsRecursive(target->leftSub);
    cout << target->stringNode << "(" << balanceFactor(target) << "), ";
    printBalanceFactorsRecursive(target->rightSub);
}

//If string has an existing node in tree, return true
bool AVLTree::search(const string& key) const {
    //start search from root to bottom
    return search(root, key);
}

//Search tree for node recursively
bool AVLTree::search(Node* target, const string& key) const {
    //start from node passed in by parameter
    Node* currNode = target;
    while (currNode != nullptr) {
        //if string in currNode matches key, node is found
        if (currNode->stringNode == key) {
            return true;
        }
        //if key is less than string in currNode, traverse down left subtree and recursively call searchRecursive function
        else if (key < currNode->stringNode) {
            return search(currNode->leftSub, key);
        }
        //if key is greater than string in currNode, traverse down right subtree and recursively call searchRecursive function
        else {
            return search(currNode->rightSub, key);
        }
    }
    //if node is not found in tree, return false
    return false;
}

//Traverse tree and return node that matches the key
Node* AVLTree::searchNode(Node* currNode, const string& key) const {
    while (currNode != nullptr) {
        //if string in currNode matches key, node is found
        if (currNode->stringNode == key) {
            return currNode;
        }
        //if key is less than string in currNode, traverse down left subtree 
        else if (key < currNode->stringNode) {
            currNode = currNode->leftSub;
        }
        //if key is greater than string in currNode, traverse down right subtree 
        else {
            currNode = currNode->rightSub;
        }
    }
    //if node is not found in tree, return nullptr
    return nullptr;
}

void AVLTree::preOrder() const {
    //Start printing from root
    preOrderRecursive(root);
}

//Recursive helper function of preOrder 
void AVLTree::preOrderRecursive(Node* target) const {
    //Base case: if tree is empty or reached end of tree, return
    if (target == nullptr) {
        return;
    }
    cout << target->stringNode << "(" << target->count << ")" << ", ";
    //recursively call pring on left subtree
    preOrderRecursive(target->leftSub);
    //recursively call print on right subtree
    preOrderRecursive(target->rightSub);
}
