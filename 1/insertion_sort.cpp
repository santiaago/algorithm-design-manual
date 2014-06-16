// insertion_sort.cpp: santiaago
// Description: a program makes an insertion sort

#include <iostream>
using namespace std;

void Swap(int *a, int *b){
  int t = *a;
  *a = *b;
  *b = t;
}

void PrintArray(int s[], int size){
  for(int i = 0; i < size; i++){
    cout << s[i] << " ";
  }
  cout << endl;
}

void InsertionSort(int s[], int n){
  int i, j;
  for(i = 1; i < n; i++){
    j = i;
    while( (j > 0) && (s[j] < s[j-1]) ){
      PrintArray(s, n);
      Swap(&s[j], &s[j-1]);
      j = j - 1;
    }
  }
}

int main()
{
  cout <<  "insertion sort:" << endl;
  int unsorted_array[5] = {2,3,5,4,1};
  cout << "unsorted array: ";
  PrintArray(unsorted_array, 5);
  InsertionSort(unsorted_array, 5);
  cout << "sorted array: ";
  PrintArray(unsorted_array, 5);
}
