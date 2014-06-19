//  selection_sort.cpp: santiaago
//  Description: selection sort algorithm

#include <iostream>
#include <limits>
using namespace std;


void swap(int &a, int &b);
void selection_sort(int a[], unsigned int size);
void selection_sort_ex(int a[], int size);
void printArray(const int a[], const unsigned int size, const unsigned int sorted_point);

int main(){
  cout << "selection sort" << endl;
  int a[10] = {9,8,7,4,5,6,3,2,1,0};
  // selection_sort(a, 10);
  selection_sort_ex(a, 10);
}

void swap(int &a, int &b){
  int t = a;
  a = b;
  b = t;
}

void selection_sort(int a[], unsigned int size){
  unsigned int sorted_point(0);

  while(sorted_point < size){
    unsigned int min(numeric_limits<int>::max());
    unsigned int arg_min(0);
    for(int i = sorted_point; i < size; i++){
      if(a[i] < min){
	min = a[i];
	arg_min = i;
      }
    }
    swap(a[sorted_point], a[arg_min]);
    printArray(a, size, sorted_point);
    sorted_point++;
  }
}

void selection_sort_ex(int a[], int size){
  int i,j;
  int min;
  
  for(i = 0; i < size; i++){
    min = i;
    for(j = i + 1; j < size; j++){
      if( a[j] < a[min]){
	min = j;
      }
    }
    swap(a[i], a[min]);
    printArray(a, size, i);
  }
}

void printArray(const int a[], const unsigned int size, const unsigned int sorted_point){
  for(int i = 0; i < size; i++){
    cout << a[i];
    if(i == sorted_point){
      cout << " | ";
    } else{
      cout << " ";
    }
  }
  cout << endl;
}
