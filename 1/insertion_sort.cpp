// insertion_sort.cpp: santiaago
// Description: a program makes an insertion sort

#include <iostream>
using namespace std;

template<typename T>
void Swap(T *a, T *b){
  T t = *a;
  *a = *b;
  *b = t;
}

template<typename T>
void PrintArray(T s[], int size){
  for(int i = 0; i < size; i++){
    cout << s[i] << " ";
  }
  cout << endl;
}

template<typename T>
void InsertionSort(T s[], int n){
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
  cout <<  "insertion sort: int" << endl;
  int unsorted_array[5] = {2,3,5,4,1};
  cout << "unsorted array: ";
  PrintArray(unsorted_array, 5);
  InsertionSort(unsorted_array, 5);
  cout << "sorted array: ";
  PrintArray(unsorted_array, 5);

  cout <<  "insertion sort: char" << endl;
  char unsorted_char_array[] = "insertionsort";
  cout << "unsorted array: ";
  PrintArray(unsorted_char_array, 13);
  InsertionSort(unsorted_char_array, 13);
  cout << "sorted array: ";
  PrintArray(unsorted_char_array, 13);

}
