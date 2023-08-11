#include <iostream>
#include "IntList.h"

using namespace std;

//Destructor starts at beginning of the list and deletes/deallocates memory in list except for dummy nodes
IntList::~IntList() {
    IntNode* curr = dummyHead->next;
    IntNode* temp = curr;
    //start at node after dummyHead and delete nodes before dummyTail
    while (curr != dummyTail) {
        curr = curr->next;
        delete temp;
        temp = curr;        
    }
}

void IntList::push_front(int value) {
    IntNode *newNode = new IntNode(value);
    //Saves node to insert before
    IntNode *firstNode = dummyHead->next;
    //Set next and prev for new node
    newNode->next = firstNode;
    newNode->prev = dummyHead;

    dummyHead->next = newNode;
    firstNode->prev = newNode;
}

void IntList::pop_front() {
    if (dummyHead->next == dummyTail) {
        return;
    }
    //removeNode is first node in list
    IntNode *removeNode = dummyHead->next;
    //sucNode is second node in list
    IntNode *sucNode = removeNode->next;

    dummyHead->next = sucNode;
    sucNode->prev = nullptr;
    delete removeNode;
}

void IntList::push_back(int value) {
    if (empty()) {
        this->push_front(value);
    }
    else {
        IntNode *newNode = new IntNode(value);
        //Saves node to insert after
        IntNode *lastNode = dummyTail->prev;
        //Set next and prev for new node
        newNode->prev = lastNode;
        newNode->next = dummyTail;

        dummyTail->prev = newNode;
        lastNode->next = newNode;
    }
}

void IntList::pop_back() {
    if (empty()) {
        return;
    }
    //removeNode is last node in list
    IntNode *removeNode = dummyTail->prev;
    //prevNode is second to last node in list
    IntNode *prevNode = removeNode->prev;

    dummyTail->prev = prevNode;
    prevNode->next = dummyTail;
    delete removeNode;
}

bool IntList::empty() const {
    //if there are no nodes between dummyHead and dummyTail, return true
    if (dummyHead->next == dummyTail) {
        return true;
    }
    else {
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    //Empty list
    if (rhs.empty()) {
        return out;
    }
    //One node in list
    else if (rhs.dummyHead->next == rhs.dummyTail->prev) {
        out << rhs.dummyHead->next->data;
    }
    else {
        IntNode *curr = rhs.dummyHead->next;
        //Start at node after dummyHead and print with space until node before dummyTail
        while (curr != rhs.dummyTail->prev) {
            out << curr->data << " ";
            curr = curr->next;
        }
        //Print node before dummyTail without space
        out << curr->data;
    }
return out;
}

void IntList::printReverse() const {
    if (empty()) {
        return;
    }
    //One node in list
    else if (dummyHead->next == dummyTail->prev) {
        cout << dummyHead->next->data;
    }
    else {
        IntNode *curr = dummyTail->prev;
        //Start at node before dummyTail and print with space until node after dummyHead
        while (curr != dummyHead->next) {
            cout << curr->data << " ";
            curr = curr->prev;
        }
        //Print node after dummyHead without space
        cout << curr->data;
    }
}
