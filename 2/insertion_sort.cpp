//  insertion_sort.cpp: santiaago
//  Description: insertion sort algorithm

#include <iostream>

using namespace std;

void insertion_sort(int a[], unsigned int size);
void swap(int &a, int &b);
void printArray(int a[], unsigned int size);

int main(){
  cout << "insertion sort" << endl;
  int a[10] = {9,8,7,4,5,6,3,2,1,0};
  insertion_sort(a, 10);
}

void insertion_sort(int a[], unsigned int size){
  for(int i = 1; i < size; i++){
    int j = i;
    while( (j > 0) && a[j] < a[j - 1]){
      swap(a[j], a[j-1]);
      printArray(a, size);
      j--;
    }
  }
}

void swap(int &a, int &b){
  int t = a;
  a = b;
  b = t;
}

void printArray(int a[], unsigned int size){
  for(int i = 0; i < size; i++){
    cout << a[i] << " ";
  }
  cout << endl;
}
