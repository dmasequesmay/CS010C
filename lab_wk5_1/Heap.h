#ifndef __HEAP_H
#define __HEAP_H

#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];      // Notice this is an array of PrintJob pointers
  unsigned int numItems;  //current number of items in heap

public:
  /*Initializes an empty heap.*/
  Heap();

  /*Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void enqueue ( PrintJob* );

  /*Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void dequeue ( );

  /*Returns the node with highest priority.*/
  PrintJob* highest ( );

  /*Prints the PrintJob with highest priority in the following format:
  Priority: priority, Job Number: jobNum, Number of Pages: numPages
  (Add a new line at the end.)*/
  void print ( );

  /*Helper function that prints the heap from root to end*/
  void printHeap();

private:
  /*This function is called by dequeue function
  to move the new root down the heap to the 
  appropriate location.*/
  void trickleDown(int &);

  //You can include additional private helper functions here
};
#endif
