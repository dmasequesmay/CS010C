#include <iostream>
#include "IntList.h"

using namespace std;

int main () {

IntList list1;
list1.push_front(1);
list1.push_front(2);
list1.push_front(3);
cout << list1 << endl;

list1.pop_front();
cout << list1 << endl;

list1.push_back(0);
cout << list1 << endl; 

list1.pop_back();
cout << list1 << endl;

IntList list2;
list2.push_back(1);
list2.push_back(2);
list2.push_back(3);
list2.push_back(4);
list2.push_back(5);
cout << list2 << endl;
list2.printReverse();

return 0;

}