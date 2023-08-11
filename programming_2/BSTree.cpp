#include <iostream>
#include <string>
#include "BSTree.h"

using namespace std;

//Constructor creates an empty tree
BSTree::BSTree() {
    root = nullptr;
}

//Destructor deletes the root and all the subtrees
BSTree::~BSTree() {
    delete root;
    root = nullptr;
}

//Insert a node in the tree, takes in string parameter to insert
void BSTree::insert(const string &newString) {
    //if node with newString already exists, increment count by 1
    if (search(newString)) {
        Node* targetNode = searchNode(root, newString);
        targetNode->SetCountNode(targetNode->GetCountNode() + 1);
        return;
    }
    //if node with Newstring does not already exist in tree, 
    //create new node initializing stringNode with newString and count with 1
    Node* newNode = new Node(newString, 1);
    //if tree is empty, initialize root with newNode
    if (root == nullptr) {
        root = newNode;
    }
    else {
        //if tree is not empty, traverse tree to find correct place to insert
        //while loop starts at root
        Node* currNode = root;
        while (currNode != nullptr) {
            //currNode moves to left subtree if newNode string is less than currNode string
            if (newNode->GetStringNode() < currNode->GetStringNode()) {
                //if there is no left subtree, insert newNode
                if (currNode->GetLeftSub() == nullptr) {
                    currNode->SetLeftSub(newNode);
                    currNode = nullptr;
                }
                //keep going down the left subtree
                else {
                    currNode = currNode->GetLeftSub();
                }
            }
            //currNode moves to right subtree if newNode string is greater than currNode string
            else {
                //if there is no right subtree, insert newNode
                if (currNode->GetRightSub() == nullptr) {
                    currNode->SetRightSub(newNode);
                    currNode = nullptr;
                }
                //keep going down the right subtree
                else {
                    currNode = currNode->GetRightSub();
                }
            }
        }
    }
}

//Remove a node in tree, takes in string parameter to remove
void BSTree::remove(const string& key) {
    //if node does not exist in tree, return 
    if (!search(key)) {
        return;
    }
    //if node exists in tree and the node count is greater than 1, decrement count by 1
    if (search(key) && (searchNode(root, key)->GetCountNode() > 1)) {
        Node* removeNode = searchNode(root, key);
        removeNode->SetCountNode(removeNode->GetCountNode() - 1);
        return;
    }
    //if tree is just root with no left or right child, delete root by calling destructor
    if ( (root == searchNode(root,key)) && (root->GetLeftSub() == nullptr) && (root->GetRightSub() == nullptr) ) {
        delete root;
        root = nullptr;
    }
    //to remove node, call removeRecursive helper function that takes root and key parameter
    removeRecursive(root, key);
}

//Search tree for node to remove and remove node when found
void BSTree::removeRecursive(Node* currNode, const string& key) {
    //if node to remove does not exist, return
    if (currNode == nullptr) {
        return;
    }
    //if node in tree is found, remove node based on Case 1, Case 2, or Case 3
    if (currNode->GetStringNode() == key) {
        Node* succNode = nullptr;
        string succNodeString;
        //Case 1: Removing a leaf (no left subtree and no right subtree)
        if ((currNode->GetLeftSub() == nullptr) && (currNode->GetRightSub() == nullptr))  {
            //Find the parent node of currNode using GetParent() function
            Node* parentNode = GetParent(root, currNode);
            //delete currNode and set parentNode subtree pointer to nullptr
            if (parentNode->GetLeftSub() == currNode) {
                parentNode->SetLeftSub(nullptr);
            }
            else {
                parentNode->SetRightSub(nullptr);
            }
            delete currNode;
        }
        //Case 2: Removing a left Child (if currNode only has left child or 2 children)
        else if (currNode->GetLeftSub() != nullptr) {
            //find the largest node in the left subtree by going to left subtree and traversing all the way down right subtree
            succNode = currNode->GetLeftSub();

            while (succNode->GetRightSub() != nullptr) {
                succNode = succNode->GetRightSub();
            }

            //largest node in left subtree is the successor node
            succNodeString = succNode->GetStringNode();

            //Copy the count value from the successor node
            currNode->SetCountNode(succNode->GetCountNode());
            
            //starting from currNode, recursively call remove helper function while the successor node still exists in tree
            while (searchRecursive(currNode, succNodeString)) {
                removeRecursive(currNode->GetLeftSub(), succNodeString);
            }

            //Copy the string value from the successor node to correct node
            currNode->SetStringNode(succNodeString);
        }
        //Case 3: Removing right child 
        else {
            //find the smallest node in the right subtree by going to the right subtree and traversing to the top of the right subtree
            succNode = currNode->GetRightSub();

            while (succNode->GetLeftSub() != nullptr) {
                succNode = succNode->GetLeftSub();
            }

            //smallest node in right subtree is the successor node
            succNodeString = succNode->GetStringNode();

            //Copy the count value from the successor node
            currNode->SetCountNode(succNode->GetCountNode());

            //starting from currNode, recursively call remove helper function while the successor node still exists in tree
            while (searchRecursive(currNode, succNodeString)) {
                removeRecursive(currNode->GetRightSub(), succNodeString);
            }

            //Copy the string value from the successor node to correct node
            currNode->SetStringNode(succNodeString);
        }
    }
    //if node in tree is not found yet, traverse down tree
    //if node currNode string is greater than key to be removed, recursively call remove helper function starting from left subtree of currNode
    else if (currNode->GetStringNode() > key) {
        removeRecursive(currNode->GetLeftSub(), key);
    }
    //if node currNode string is less than key to be removed, recursively call remove helper function starting from right subtree of currNode
    else {
        removeRecursive(currNode->GetRightSub(), key);
    }

}

//Return node of the parent of a target node
Node* BSTree::GetParent(Node* subtreeRoot, Node* targetNode) {
    //if subtreeRoot is nullptr, then tree is empty and parent is nullptr;
    if (subtreeRoot == nullptr) {
        return nullptr;
    }
    //if targetNode is child of subtreeRoot, return subtreeRoot is parent node
    if ((subtreeRoot->GetLeftSub() == targetNode) || (subtreeRoot->GetRightSub() == targetNode)) {
        return subtreeRoot;
    }
    //if node in tree is not found yet, traverse down tree
    //if targetNode is less than subtreeRoot, recursively call function starting from left subtree of subtreeRoot
    if (targetNode->GetStringNode() < subtreeRoot->GetStringNode()) {
        return GetParent(subtreeRoot->GetLeftSub(), targetNode);
    }
    //if targetNode is greater than subtreeRoot, recursively call function starting from right subtree of subtreeRoot
    else {
        return GetParent(subtreeRoot->GetRightSub(), targetNode);
    }
    //if can not find node, return parent node as nullptr
    return nullptr;
}

//If string has an existing node in tree, return true
bool BSTree::search(const string& key) const {
    //start search from root to bottom
    return searchRecursive(root, key);
}

//Search tree for node recursively
bool BSTree::searchRecursive(Node* target, const string& key) const {
    //start from node passed in by parameter
    Node* currNode = target;
    while (currNode != nullptr) {
        //if string in currNode matches key, node is found
        if (currNode->GetStringNode() == key) {
            return true;
        }
        //if key is less than string in currNode, traverse down left subtree and recursively call searchRecursive function
        else if (key < currNode->GetStringNode()) {
            return searchRecursive(currNode->GetLeftSub(), key);
        }
        //if key is greater than string in currNode, traverse down right subtree and recursively call searchRecursive function
        else {
            return searchRecursive(currNode->GetRightSub(), key);
        }
    }
    //if node is not found in tree, return false
    return false;
}

//Traverse tree and return node that matches the key
Node* BSTree::searchNode(Node* currNode, const string& key) const {
    while (currNode != nullptr) {
        //if string in currNode matches key, node is found
        if (currNode->GetStringNode() == key) {
            return currNode;
        }
        //if key is less than string in currNode, traverse down left subtree 
        else if (key < currNode->GetStringNode()) {
            currNode = currNode->GetLeftSub();
        }
        //if key is greater than string in currNode, traverse down right subtree 
        else {
            currNode = currNode->GetRightSub();
        }
    }
    //if node is not found in tree, return nullptr
    return nullptr;
}

//Return the largest string in the tree
string BSTree::largest() const {
    //if tree is empty, return empty string
    if (root == nullptr) {
        return "";
    }
    //start at root and traverse down right subtree
    Node* currNode = root;
    while (currNode->GetRightSub() != nullptr) {
        currNode = currNode->GetRightSub();
    }
    return currNode->GetStringNode();
}

//Return the smallest string in the tree
string BSTree::smallest() const {
    //if tree is empty, return empty string
    if (root == nullptr) {
        return "";
    }
    //start at root and traverse down left subtree
    Node* currNode = root;
    while (currNode->GetLeftSub() != nullptr) {
        currNode = currNode->GetLeftSub();
    }
    return currNode->GetStringNode();
}

//Return height of node that matches key
int BSTree::height(const string& key) const {
    //find node that matches key  
    Node* currNode = searchNode(root, key);
    int count = 0;
    //traverse down tree, each time currNode moves down to child subtree, increment count
    while (currNode != nullptr) {
        //return count if node is a leaf
        if ( (currNode->GetLeftSub() == nullptr) && (currNode->GetRightSub() == nullptr) ) {
            return count;
        }
        else if (currNode->GetLeftSub() != nullptr) {
            currNode = currNode->GetLeftSub();
            count++;
        }
        else {
            currNode = currNode->GetRightSub();
            count++;
        }
    }

    //if node in key is not found, return height as -1
    return -1;
}

//Print the nodes of the tree by traversing down tree from left to right
void BSTree::preOrder() {
    //Start printing from root
    preOrderRecursive(root);
}

//Recursive helper function of preOrder 
void BSTree::preOrderRecursive(Node* target) {
    //Base case: if tree is empty or reached end of tree, return
    if (target == nullptr) {
        return;
    }
    cout << target->GetStringNode() << "(" << target->GetCountNode() << ")" << ", ";
    //recursively call pring on left subtree
    preOrderRecursive(target->GetLeftSub());
    //recursively call print on right subtree
    preOrderRecursive(target->GetRightSub());
}

//Print the nodes of the tree from smallest node to largest node
void BSTree::inOrder() {
    //start printing from root
    inOrderRecursive(root);
}

//Recursive helper function of inOrder
void BSTree::inOrderRecursive(Node* target) {
    //Base case: if tree is empty or reached end of tree, return
    if (target == nullptr) {
        return;
    }
    //start at smallest node from left subtree and recursively call print on left subtree
    inOrderRecursive(target->GetLeftSub());
    cout << target->GetStringNode() << "(" << target->GetCountNode() << ")" << ", ";
    //recursively call print on right subtree
    inOrderRecursive(target->GetRightSub());
}

//Print the nodes of the tree by traversing down tree from right to left
void BSTree::postOrder() {
    //start printing from root
    postOrderRecursive(root);
}

//Recursive helper function postOrderRecursive
void BSTree::postOrderRecursive(Node* target) {
    //Base case: if tree is empty or reached end of tree, return
    if (target == nullptr) {
        return;
    }
    //recursively call print on right subtree
    postOrderRecursive(target->GetLeftSub());
    //recursively call print on left subtree
    postOrderRecursive(target->GetRightSub());
    cout << target->GetStringNode() << "(" << target->GetCountNode() << ")" << ", ";
}