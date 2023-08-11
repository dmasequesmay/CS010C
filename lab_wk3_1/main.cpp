#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    //Initializes minIndex with the first index searched
    int minIndex = index;
    //Loop starts at index from parameter and stops at end of vector
    for (unsigned int i = index; i < vals.size(); ++i) {
        //Compares each element in vector and changes minIndex to index with the smallest val
        if (vals.at(minIndex) >= vals.at(i)) {
            minIndex = i;
        }
    }
return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    //If vector size is 1, list is already sorted
    if (vals.size() <= 1) {
        return;
    }
    //If vector size is 2, only compare/sort 2 values
    else if (vals.size() == 2) {
        T temp;
        if (vals.at(0) > vals.at(1)) {
            temp = vals.at(0);
            vals.at(0) = vals.at(1);
            vals.at(1) = temp;
        }
        else {
            return;
        }
    }
    //If vector size is greater than 2
    else{
        int indexSmallest;
        int possIndexSmallest;
        T temp;
        //Loop starts at first element of vector and ends at second to last element
        for (unsigned int i = 0; i < vals.size() - 1; ++i) {
            indexSmallest = i; 
            //Call min_index function to find index of smallest element in remaining list
            possIndexSmallest = min_index(vals, i + 1);
            //If element at possIndexSmallest is less than element at indexSmallest, swap variables
            if (vals.at(possIndexSmallest) < vals.at(indexSmallest)) {
                temp = vals.at(indexSmallest);
                vals.at(indexSmallest) = vals.at(possIndexSmallest);
                vals.at(possIndexSmallest) = temp;
            }    
        }
    }
}

template<typename T>
T getElement(vector<T> vals, int index) {
    //last possible index of vals vector
    int lastIndex = vals.size() - 1;
    //If index from parameter is less than 0 or greater than size - 1, throw out of range error
    try {
        if ((index < 0) || (index > lastIndex)) {
            throw std::out_of_range("out of range exception occured");
        }
    }
    //Print out of range error
    catch (const std::out_of_range& excpt) {
        cout << excpt.what() << endl;
    }
    //If index is valid, print the value at index
    return vals.at(index);
}
 
vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main () {
//Part A
    // vector<float> nums;
    // float userVal;
    // for (unsigned int i = 0; i < 5; ++i) {
    //     cout << "Enter val: ";
    //     cin >> userVal;
    //     cout << endl;
    //     nums.push_back(userVal);
    // }
    // for (unsigned int i = 0; i < nums.size(); ++i) {
    //     cout << nums.at(i) << " ";
    // }
    // cout << endl;
    // selection_sort(nums);
    // for (unsigned int i = 0; i < nums.size(); ++i) {
    //     cout << nums.at(i) << " ";
    // }
    // cout << endl;
//Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
return 0;

}


