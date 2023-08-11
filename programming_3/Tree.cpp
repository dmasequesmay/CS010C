#include <iostream>
#include <string>
#include "Node.h"
#include "Tree.h"

using namespace std;

/// default constructor initializes root to nullptr, creates an empty tree
Tree::Tree() {
    root = nullptr;
}

//destructor calls helper function to delete nodes recursively
Tree::~Tree() {
    destructor(root);
}

//passes in node to delete and traverses through tree to delete nodes recursively
void Tree::destructor(Node* target) {
    //base case: return if target does not exist
    if (target == nullptr) {
        return;
    }
    //delete starting from left subtree, middle subtree, then right subtree. Finally, delete root at the end
    destructor(target->left);
    destructor(target->middle);
    destructor(target->right);
    delete target;
}

//insert a new title
void Tree::insert(const string &title) {
    //base case: if tree is empty, assign root to a new node with title
    if (root == nullptr) {
        root = new Node(title);
        return;
    }
    //if a tree already exists, pass in root and new title to insert
    insertRecursive(root, title);

}

//helper function that recursively traverses down tree to find correct position to insert
void Tree::insertRecursive(Node* target, const string &key) {
    //if target is a leaf (left, middle, or right pointers are nullptr)
    if (target->IsLeaf()) {
        //if target is not full, large is empty
        if (!target->IsNodeFull()) {
            target->large = key;
            //if key is less than small value in target, swap variables
            if (key < target->small) {
                string temp = target->small;
                target->small = target->large;
                target->large = temp;
            }
        }
        //if target is full, split and insert key
        else {
            SplitInsert(target, key);
        }
    }
    //if target only has left and middle pointers
    else if (target->large.empty()) {
        //go to left subtree if key is smaller than target small
        if (key < target->small) {
            insertRecursive(target->left, key);
        }
        //go to right subtree if key is larger than target small
        else if (key > target->small) {
            insertRecursive(target->middle, key);
        }
    }
    //if target has left, middle, and right pointers
    else {
        //go to left subtree if key is smaller than target small
        if (key < target->small) {
            insertRecursive(target->left, key);
        }
        //go to right subtree if key is larger than target large
        else if (key > target->large) {
            insertRecursive(target->right, key);
        }
        //go to middle subtree if key is between target small and target large
        else {
            insertRecursive(target->middle, key);
        }
    }
}

//helper function of insertRecursive that splits the tree to insert a new title
void Tree::SplitInsert(Node* target, const string &key) {
    //if target is root
    if (target == root) {
        Node* splitLeft;
        Node* splitRight;
        Node* toDelete;
        //if target is a leaf (left, middle, and right pointers are nullptr)
        if ( target->IsLeaf() ) {
            //if inserting a key that is less than target small, make left subtree contain key, right subtree contain target large, parent does not change
            if (key < target->small) {
                splitLeft = new Node(key);
                splitRight = new Node(target->large);
                //delete large
                target->large = "";
            }
            //if inserting a key that is greater than target large, make left subtree contain target small, right subtree contain key, parent becomes target large
            else if (key > target->large) {
                splitLeft = new Node(target->small);
                splitRight = new Node(key);
                //swap small and large and then delete large
                target->small = target->large;
                target->large = "";
            }
            //if inserting a key that is between target small and target large, make left subtree contain target small, right subtree contain target large, parent becomes key
            else {
                splitLeft = new Node(target->small);
                splitRight = new Node(target->large);
                target->small = key;
                target->large = "";
            }
            target->left = splitLeft;
            target->middle = splitRight;
        }
        //if target is not a leaf
        else {
            //if key is less than target small
            if (key < target->small) {
                //splitLeft contains key and left subtree of splitLeft contains target left large. delete target left
                splitLeft = new Node(key);
                toDelete = target->left;
                splitLeft->left = new Node(target->left->large);
                delete toDelete;
                target->left = nullptr;
                //splitRight contains target large
                //if target middle is full, splitLeft middle subtree takes middle small and splitRight left subtree takes middle large. delete target middle
                toDelete = target->middle;
                splitLeft->middle = new Node(target->middle->small);
                splitRight = new Node(target->large);
                splitRight->left = new Node(target->middle->large);
                delete toDelete;
                target->middle = nullptr;
                //splitRight middle contains target right. delete target right
                toDelete = target->right;
                splitRight->middle = new Node(target->right->small, target->right->large);
                delete toDelete;
                target->right = nullptr;
            }
            target->large = "";
            //reassign target left and middle subtrees
            target->left = splitLeft;
            target->middle = splitRight;
        }
    }
    else {
        //parent node of target
        Node* parent = GetParent(target->small);
        //if parent node of targe is not full (no large), split by inserting in parent
        if (!parent->IsNodeFull()) {
            //if key is less than target small, target small moves to parent
            if (key < target->small) {
                parent->large = target->small;
                //swap if large is greater than small
                if (parent->large < parent->small) {
                    string temp = parent->small;
                    parent->small = parent->large;
                    parent->large = temp;
                }
                //reassign parent left, middle, and right pointers
                if (parent->left == target) {
                    parent->middle = parent->left;
                    parent->left = new Node(target->small);
                    parent->middle->small = parent->middle->large;
                    parent->middle->large = "";
                }
                else if (parent->middle == target) {
                    parent->middle = parent->right;
                    parent->right = new Node(target->large);
                    parent->middle->large = "";
                }
            }
            //if key is greater than target small but less than target large, key moves to parent
            if ( (key > target->small) && (key < target->large) ){
                parent->large = key;
                //swap if large is greater than small
                if (parent->large < parent->small) {
                    string temp = parent->small;
                    parent->small = parent->large;
                    parent->large = temp;
                }
                //if target is parent left and parent only has left and middle pointers
                if ((parent->left == target) && (parent->right == nullptr)) {
                    //create a right pointer and new node for middle pointer
                    parent->right = parent->middle;
                    parent->middle = new Node(target->large);
                    target->large = "";
                } 
                //if target is parent middle and parent only has left and middle pointers
                else if ((parent->middle == target) && (parent->right == nullptr)) {
                    //create a right pointer with copy of target large and delete parent middle large
                    parent->right = new Node(target->large);
                    parent->middle->large = "";
                }
            }
            //if key is greater than target small, target large moves to parent
            if (key > target->small) {
                parent->large = target->large;
                parent->middle->large = "";
                //swap if large is greater than small
                if (parent->large < parent->small) {
                    string temp = parent->small;
                    parent->small = parent->large;
                    parent->large = temp;
                }
                //if target is parent left and parent only has left and middle pointers
                if ((parent->left == target) && (parent->right == nullptr)) {
                    //create right and make middle new node containing target large
                    parent->right = parent->middle;
                    parent->middle = new Node(target->large);
                } 
                //if target is parent middle and parent only has left and middle pointers
                else if ((parent->middle == target) && (parent->right == nullptr)) {
                    //create right with new node of key
                    parent->right = new Node(key);
                }
            }
        }
        //if parent node is full, call SplitInsert recursively to split parent first
        else {
            if (key < target->small) {
                SplitInsert(parent, target->small);
            }
            else if(key > target->large) {
                SplitInsert(parent, target->large);
            }
            else {
                SplitInsert(parent, key);
            }
            insertRecursive(root, key);
        }
    }
}

//print tree starting from root then traversing to left, middle, and right subtree
void Tree::preOrder() const {
    preOrderRecursive(root);
    cout << endl;
}

//helper function of preOrder to print each node recursively
void Tree::preOrderRecursive(Node* target) const {
    if (target == nullptr) {
        return;
    }
    cout << target->small << ", ";
    preOrderRecursive(target->left);
    if (!target->large.empty()) {
        cout << target->large << ", ";
    }
    preOrderRecursive(target->middle);
    preOrderRecursive(target->right);
}

//print tree in alphabetical order
void Tree::inOrder() const {
    inOrderRecursive(root);
    cout << endl;
}

//helper function of inOrder to print each node recursively
void Tree::inOrderRecursive(Node* target) const {
    if (target == nullptr) {
        return;
    }
    inOrderRecursive(target->left);
    cout << target->small << ", ";
    inOrderRecursive(target->middle);
    if (!target->large.empty()) {
        cout << target->large << ", ";
    }
    inOrderRecursive(target->right);
}

//print tree starting from left subtree and middle subtree going up root and then right subtree going back up to root
void Tree::postOrder() const {
    postOrderRecursive(root);
    cout << endl;
}

//helper function of postOrder to print each node recursively
void Tree::postOrderRecursive(Node* target) const {
    if (target == nullptr) {
        return;
    }
    postOrderRecursive(target->left);
    postOrderRecursive(target->middle);
    cout << target->small << ", ";
    postOrderRecursive(target->right);
    if (!target->large.empty()) {
        cout << target->large << ", ";
    }

}

//remove the key passed in by parameter
void Tree::remove(const string &key) {
    //if key is not in tree, return because there is nothing to remove
    if (!search(key)) {
        return;
    }
    removeRecursive(root, key);

}

//helper function of remove to find correct node to remove key
void Tree::removeRecursive(Node* target, const string &key) {
    //if tree only has root
    if ( (target == root) && target->IsLeaf() ) {
        //if node is full, delete small or large
        if (target->IsNodeFull()) {
            if (target->small == key) {
                target->small = target->large;
            }
            target->large = "";
            return;
        }
        //if node only contains key, delete node to make tree empty
        else {
            delete target;
            root = nullptr;
            return;
        }
    }
    //target node contains key 
    if ( (target->small == key) || (target->large == key) ) {
        //if target is full, remove small or large
        if (target->IsNodeFull()) {
            if (target->small == key) {
                target->small = target->large;
            }
            target->large = "";
        }
        //if target small matches key, remove the entire node by calling Split
        else {
            SplitRemove(target, key);
        }
    }
    //if target does not match key, call remove recursively to traverse down the tree to find correct node
    else if (target->large.empty()) {
        if (key < target->small) {
            removeRecursive(target->left, key);
        }
        else if (key > target->small) {
            removeRecursive(target->middle, key);
        }
    }
    else {
        if (key < target->small) {
            removeRecursive(target->left, key);
        }
        else if (key > target->large) {
            removeRecursive(target->right, key);
        }
        else {
            removeRecursive(target->middle, key);
        }
    }
}

//helper function of removeRecursive to shift node positions after deleting a node
void Tree::SplitRemove(Node* target, const string & key) {
    Node* splitLeft;
    Node* splitRight;
    Node* toDelete = target;
    Node* parent = GetParent(target->small);
    //if target is root and only has left and middle pointers, make left subtree target left and right subtree target middle
    if ((target == root) && (target->right == nullptr)) {
        splitLeft = target->left;
        splitRight = target->middle;
    }
    //if target is root and has left, middle, and right pointers
    else {
        //if target is parent left, rotate left by bringing root down to parent left
        if (parent->left == target) {
            splitLeft = parent;
            splitRight = parent->middle;
        }
        //if target is parent middle, rotate right by bringing root down to parent middle
        else if (parent->middle == target) {
            splitLeft = parent->left;
            splitRight = parent;  
        }
    }
    //if left and right subtree only contain one value, create new node that contains both values
    if ((!splitLeft->IsNodeFull()) && (!splitRight->IsNodeFull())) {
        target = new Node(splitLeft->small, splitRight->small);
    } 
    //reassign root if necessary
    if (parent == root) {
        root = target;
    }
    //delete former tree
    delete toDelete;
    delete splitLeft;
    delete splitRight;
    
}

//search if a node exists in the tree by passing in key
bool Tree::search(const string &key) const {
    return searchRecursive(root, key);
}

//helper function of search that traverses down tree to compare key to each node value
bool Tree::searchRecursive(Node* target, const string &key) const {
    //base case: if node does not exist, return false
    if (target == nullptr) {
        return false;
    }
    //if node contains matching key, return true
    if ( (target->small == key) || (target->large == key) ) {
        return true;
    }
    //if target does not contain key, recursively call search to traverse down tree
    if (key < target->small) {
        return searchRecursive(target->left, key);
    }
    else if (key < target->large) {
        return searchRecursive(target->right, key);
    }
    else {
        return searchRecursive(target->middle, key);
    }
    return false;    
}

//return the parent of a node containing the string passed in 
Node* Tree::GetParent(const string &key) {
    //start at root
    Node* target = root;
    //if target is root, the parent is also target
    Node* parent = target;
    //start at root and stop at end of tree
    while (target != nullptr) {
        //if target contains key, return parent node
        if ( (target->small == key) || (target->large == key) ) {
            return parent;
        }
        //if target does not contain key, reassign parent and target
        parent = target; 
        //reassign target by going down different subtrees according to key
        if (target->large.empty()) {
            if (key < target->small) {
                target = target->left;
            }
            else if (key > target->small) {
                target = target->middle;
            }
        }
        else {
            if (key < target->small) {
                target = target->left;
            }
            else if (key > target->large) {
                target = target->middle;
            }
            else {
                target = target->right;
            }
        }
    }
//if parent is not found, return nullptr
return nullptr;
}


