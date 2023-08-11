#include <iostream>
using namespace std;

const int NUMBERS_SIZE = 50000;

//Generate a random integer
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

//Create an array filled with random integer
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//where pivot value is the midpoint of array,
//parition data into a low part with data less than/equal to pivot value and high part with data greater than/equal to pivot value
//returns the location of the last element of the lower partition
int Partition_midpoint(int numbers[], int i, int k) {
    int l = i;
    int h = k;
    int midpoint = i + (k - i) / 2;
    int pivot = numbers[midpoint];
    int temp;
    bool done = false;
    
    //while loop starts at beginning of the array and ends when all elements are swapped
    while (!done) {
        //incrememnt l while numbers[l] < pivot
        while (numbers[l] < pivot) {
            ++l;
        }
        //decrememnt h while pivot < numbers[h] 
        while (pivot < numbers[h]) {
            --h;
        }
        //if there are zero or one elements remaining, all numbers are partitioned. Return h
        if (l >= h) {
            done = true;
        }
        else {
            //swap numbers[l] and numbers[h], update l and h
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            ++l;
            --h;
        }
    }

    return h;

}

/*This function sorts the given array in the range from i to k using quicksort method. 
In this function, pivot is the midpoint element (numbers[(i+k)/2]).
(implementation of this function is given in section 21.5) */
void Quicksort_midpoint(int numbers[], int i, int k) {
    //Base case: If there are 1 or zero elements to sort, partition is already sorted
    if (i >= k) {
        return;
    }
    //parition the data within the array. J is location of last element in low partition
    int j = Partition_midpoint(numbers, i, k);
    //Recursively sort low partition (i to j) 
    Quicksort_midpoint(numbers, i, j);
    //Recursively sort high partiiton (j + 1 to k)
    Quicksort_midpoint(numbers, j + 1, k);
}

//where pivot value is the median of leftmost, midpoint, and rightmost,
//parition data into a low part with data less than/equal to pivot value and high part with data greater than/equal to pivot value
//returns the location of the last element of the lower partition
int Partition_medianOfThree(int numbers[], int i, int k) {
    
    //Possible pivot: the first element of the array
    int leftmost = numbers[i];
    //Possible pivot: the middle element of the array
    int midpoint = numbers[(i + k)/2];
    //Possible pivot: the last element of the array
    int rightmost = numbers[k];
    int l = i;
    int h = k;
    int median;
    int temp;
    bool done = false;

    //Find the median of the three numbers
    if (leftmost >= midpoint) {
        if (midpoint >= rightmost) {
            median = midpoint;
        }
        else if (leftmost >= rightmost) {
            median = rightmost;
        }
        else {
            median = leftmost;
        }
    }
    else {
        if (leftmost >= rightmost) {
            median = leftmost;
        }
        else if (midpoint >= rightmost) {
            median = rightmost;
        }
        else {
            median = midpoint;
        }
    }

    //while loop starts at beginning of the array and ends when all elements are swapped
    while (!done) {
        //incrememnt l while numbers[l] < pivot
        while (numbers[l] < median) {
            ++l;
        }
        //decrememnt h while pivot < numbers[h] 
        while (median < numbers[h]) {
            --h;
        }
        //if there are zero or one elements remaining, all numbers are partitioned. Return h
        if (l >= h) {
            done = true;
        }
        else {
            //swap numbers[l] and numbers[h], update l and h
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            ++l;
            --h;
        }
    }

    return h;

}

/*This function utilizes different pivot selection technique in quicksort algorithm. 
The pivot is the median of the following three values: leftmost (numbers[i]), 
midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). 
You should modify the partition function given in section 21.5 to 
select the pivot using median-of-three technique.*/
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    //Base case: If there are 1 or zero elements to sort, partition is already sorted
    if (i >= k) {
        return;
    }
    //parition the data within the array. J is location of last element in low partition
    int j = Partition_midpoint(numbers, i, k);
    //Recursively sort low partition (i to j) 
    Quicksort_midpoint(numbers, i, j);
    //Recursively sort high partiiton (j + 1 to k)
    Quicksort_midpoint(numbers, j + 1, k);
}

/*this function sorts the given array using InsertionSort method. 
(implementation of this method is provided in section 21.3).*/
void InsertionSort(int numbers[], int numbersSize) {
    int i;
    int j;
    //Temporary variable for swap
    int temp;

    for (i = 1; i < numbersSize; ++i) {
        j = i;
        //Insert numbers[i] into sorted part
        //Stop swapping once numbers[i] is in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            //Swap numbers [j] and numbers[j-1]
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}

int main() {

    // const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
    // clock_t Start = clock();
    // //call sort function here
    // clock_t End = clock();
    // int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.

    // int numbers[] = { 10, 2, 78, 4, 45, 32, 7, 11 };
    // const int NUMBERS_SIZE = 8;
    // int i;

    //Test insertion sort
    int numbers[] = { 10, 2, 78, 4, 45, 32, 7, 11 };
    const int NUMBERS_SIZE = 8;
    int i;

    cout << "UNSORTED: ";
    for(i = 0; i < NUMBERS_SIZE; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    InsertionSort(numbers, NUMBERS_SIZE);

    cout << "SORTED: ";
    for(i = 0; i < NUMBERS_SIZE; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

return 0;
}