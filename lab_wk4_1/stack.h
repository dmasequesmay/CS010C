#include <iostream>
#include <string>
#include <stdexcept>
#define MAX_SIZE 20

#ifndef STACK_H
#define STACK_H

using namespace std;

//Class template allows stack class to store int and string values
template<class T>
class stack {

    public:
        
        //Constructor initializes data array to have size 0, no elements in array
        stack() {
            size = 0;
        }

        //Destructor sets array to have size 0, no elements in array
        ~stack() {
            size = 0; 
        }
        
        void push(T val) {
            //if array is empty, first element of array is set to val and size is incremented
           if (empty()) {
                data[0] = val;
                size++;
            }
            //if array is already full capacity (20), throw overflow error message
            else if (size + 1 > MAX_SIZE) {
                throw std::overflow_error("Called push on full stack.");
            }
            //push val to the end of the array and size is incremented
            else {
                data[size] = val;
                size++;
            }
        }

        void pop() {
            //if array is empty, can not remove element so throw out of range error message
            if (empty()) {
                throw std::out_of_range("Called pop on empty stack.");
            }
            //remove the last element of array by decrementing size
            else {
                size--;
            }
        }

        void pop_two() {
            //if array is empty, can not remove 2 elements so throw out of range error message
            if (empty()) {
                throw std::out_of_range("Called pop_two on empty stack.");
            }
            //if size of array is 1, can not remove 2 elements so throw out of range error message
            else if (size == 1) {
                throw std::out_of_range("Called pop_two on a stack of size 1.");
            }
            //remove the last 2 elements by decrementing size by 2
            else {
                size -= 2;
            }
        }

        T top() {
            //if array is empty, can not return the last element so throw underflow error message
            if (empty()) {
                throw std::underflow_error("Called top on empty stack.");
            }
            //return the last element in the array
            return data[size - 1];
        }

        bool empty() {
            //if there are no elements in array, return true because array is empty
            if (size == 0) {
                return true;
            }
            return false;
        }

    private: 

        T data[MAX_SIZE];

        int size; 

};

#endif