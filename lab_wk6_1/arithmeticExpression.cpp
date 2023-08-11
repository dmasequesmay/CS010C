#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <sstream>
#include "arithmeticExpression.h"

using namespace std;

//Constructor creates an empty tree and sets infixExpression to parameter string passed in
arithmeticExpression::arithmeticExpression(const string &newString) {
    root = nullptr;
    infixExpression = newString;
}

//Destructor deallocates nodes and sets root to nullptr to create empty tree
arithmeticExpression::~arithmeticExpression() {
    destructor(root);
}

//Helper function of destructor that passes in a node to delete
void arithmeticExpression::destructor(TreeNode* target) {
    if (target == nullptr) {
        return;
    }
    else {
        destructor(target->left);
        destructor(target->right);
        delete target;
    }
}

//Generates tree by setting infixExpression and assigning root node
void arithmeticExpression::buildTree() {

    //convertes infixExpression to postfix
    string postFix = infix_to_postfix();
    //create a stack of type TreeNode*
    stack<TreeNode*> stackTree;

    //loop builds tree by iterating through postFix equation and adding a node or operator
    for (unsigned int i = 0; i < postFix.size(); ++i) {
        //create new node with data from postFix and key according to the node number (1st node is 'a', 2nd node is 'b', etc)
        TreeNode* newNode = new TreeNode(postFix.at(i), 'a' + i);
        //if data from postFix is an operator
        if ((postFix.at(i) == '+') || (postFix.at(i) == '-') || (postFix.at(i) == '*') || (postFix.at(i) == '/') || (postFix.at(i) == '(') || (postFix.at(i) == ')') ) {
            //assign newNode right pointer with what is in stack and remove from stack
            newNode->right = stackTree.top();
            stackTree.pop();
            //if stack is not empty, assign newNode left pointer with what is left in stack and remove from stack
            if (!stackTree.empty()) {
                newNode->left = stackTree.top();
                stackTree.pop();
            }
        }
        //add the newNode to the front of the stack
        stackTree.push(newNode);
    }

    //while the stack has elements, assign root with first element in stack and remove element
    while (!stackTree.empty()){
        TreeNode *rootNode = stackTree.top();
        root = rootNode;
        stackTree.pop();
    }

}

//call recursive infix function 
void arithmeticExpression::infix() {
    infix(root);
}

//prints the tree by infix order
void arithmeticExpression::infix(TreeNode *target) {
    //base case returns if node passed in is nullptr
    if (target == nullptr) {
        return;
    }
    else {
        //if left pointer is not nullptr, print the expression inside parenthesis
        if (target->left != nullptr) {
            cout <<'(';
        }
        //recursively call infix to print data on left hand side
        infix(target->left);
        //print the operator
        cout << target->data;
        //recursively call infix to print data on right hand side
        infix(target->right);
        //if right pointer is not nullptr, end of expression and close parenthesis
        if (target->right != nullptr) {
            cout <<')';
        }
    }
}

//call recursive prefix function
void arithmeticExpression::prefix() {
    prefix(root);
}

//prints the tree by prefix order
void arithmeticExpression::prefix(TreeNode *target) {
    //base case returns if node passed in is nullptr
    if (target == nullptr) {
        return;
    }
    else {
        //print the operation first
        cout << target->data;
        //print the data from the left hand side of expression
        prefix(target->left);
        //print the data from the right hand side of expression
        prefix(target->right);
    }
}

//call recursive postfix function
void arithmeticExpression::postfix() {
    postfix(root);
}

//prints the tree by postfix
void arithmeticExpression::postfix(TreeNode *target) {
    //base case returns if node passed in is nullptr    
    if (target == nullptr) {
        return;
    }
    else {
        //print the data from the left hand side of expression
        postfix(target->left);
        //print the data from the right hand side of expression
        postfix(target->right);
        //print the operator
        cout << target->data;
    }
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    std::stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

// void arithmeticExpression::visualizeTree(const string &outputFilename){
//     ofstream outFS(outputFilename.c_str());
//     if(!outFS.is_open()){
//         cout<<"Error opening "<< outputFilename<<endl;
//         return;
//     }
//     outFS<<"digraph G {"<<endl;
//     visualizeTree(outFS,root);
//     outFS<<"}";
//     outFS.close();
//     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
//     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//     system(command.c_str());
// }