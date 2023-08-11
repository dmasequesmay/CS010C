#include <iostream>

#include "Heap.h"
#include "PrintJob.h"

using namespace std;

//default constructor initializes heap to have 0 elements
Heap::Heap() {
    numItems = 0;
}

//insert a PrintJob to heap through insertion sort
void Heap::enqueue(PrintJob* target) {
    //can not add element if numItems is greater than MAX_HEAP_SIZE
    if (numItems >= MAX_HEAP_SIZE) {
        return;
    }
    //index of target
    int targetIndex;
    //index of parent of target
    int parentIndex;
    //temp variable for swap 
    PrintJob* temp;

    //if heap is empty, insert target as root
    if (numItems == 0) {
        arr[0] = target;
        numItems++;
        return;
    }
    //if heap is not empty, insert target at end of arr and increment numItems by 1
    arr[numItems] = target;
    targetIndex = numItems;
    numItems++;
    //swap variables to move target to correct position
    while (targetIndex > 0) {
        parentIndex = (targetIndex - 1) / 2;
        //if parent dominates target, max-heap properties maintained
        if (arr[targetIndex]->getPriority() <= arr[parentIndex]->getPriority()) {
            return;
        }
        //if target dominates, max-heap properties violated, so swap variables
        else {
            temp = arr[targetIndex];
            arr[targetIndex] = arr[parentIndex];
            arr[parentIndex] = temp;
            //change target index after swap
            targetIndex = parentIndex;
        }
    }
}

//remove PrintJob at root of heap
void Heap::dequeue() {
    //if arr is empty, can not remove element
    if (numItems == 0) {
        return;
    }
    //if arr only has root, remove root
    else if (numItems == 1) {
        numItems = 0; 
        numItems--;
    }
    else {
        //replace root with last element in arr
        arr[0] = arr[numItems - 1];
        //decrememnt numItems by 1 gets rid of copy at end of array
        numItems--;
        //call trickleDown to move new root down heap to correct position
        trickleDown(0);
    }

}


//returns PrintJob at highest priority, return root
PrintJob* Heap::highest() {
    //if arr is empty, return nullptr
    if (numItems == 0) {
        return nullptr;
    }
    return arr[0];
}

//print PrintJob with the highest priority, print root
void Heap::print() {
    //if arr is empty, heap tree is empty
    if (numItems == 0) {
        return;
    }
    PrintJob* root = highest();
    cout << "Priority: " << root->getPriority();
    cout << ", Job Number: " << root->getJobNumber();
    cout << ", Number of Pages: " << root->getPages();
    cout << endl;
}

//move element at targetIndex down heap to correct position
void Heap::trickleDown(int &targetIndex) {
    //temp variable for swap
    PrintJob* temp;
    //starting from beginning of array, swap elements if target is less than current element
    for (unsigned int i = 0; i < numItems; ++i) {
        if (arr[targetIndex]->getPriority() < arr[i]->getPriority()) {    
            temp = arr[targetIndex];
            arr[targetIndex] = arr[i];
            arr[i] = temp;
        }
    }
}

//print heap from root to end 
void Heap::printHeap() {
    //start from first element print until last element in heap
    for (unsigned int i = 0; i < numItems; ++i) {
        cout << "Priority: " << arr[i]->getPriority();
        cout << ", Job Number: " << arr[i]->getJobNumber();
        cout << ", Number of Pages: " << arr[i]->getPages();
        cout << endl;
    }
}