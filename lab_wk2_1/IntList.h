#include<iostream>

#ifndef INTLIST_H
#define INTLIST_H

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {

    public:
        //Default constructor initializes empty list with dummy head and dummy tail
        IntList() 
            :   dummyHead(new IntNode(0)),
                dummyTail(new IntNode(0))
        {
            //dummyHead and dummyTail point to each other
            dummyHead->prev = nullptr;
            dummyHead->next = dummyTail;
            dummyTail->prev = dummyHead;
            dummyTail->next = nullptr;
        }
        //Destructor
        ~IntList();
        
        void push_front(int value);

        void pop_front();

        void push_back(int value);

        void pop_back();

        bool empty() const;

        friend ostream & operator<<(ostream &out, const IntList &rhs);

        void printReverse() const;

    private:
        IntNode *dummyHead;
        IntNode *dummyTail;
};

#endif