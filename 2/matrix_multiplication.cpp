//  matrix_multiplication.cpp : santiaago
//  Description: matrix multiplication algorithm

#include<iostream>

using namespace std;

void printMatrix(int** a, int size);
int** matrix_multiplication(int** a, int** b, int size);

int main(){
  cout << "matrix multiplication" << endl;
  int **a;
  int **b;
  int size = 3;
  a = new int *[size];
  b = new int *[size];

  for(int i = 0; i < size; i++){
    a[i] = new int [size];
    b[i] = new int [size];
  }

  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      a[i][j] = 1;
      b[i][j] = 2;
    }
  }
  printMatrix(a, size);
  cout << endl;
  printMatrix(b, size);
  cout << endl;
  int ** c = matrix_multiplication(a, b, size);
  printMatrix(c, size);
}

void printMatrix(int** a, int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
}

int** matrix_multiplication(int** a, int** b, int size){
  int **c;
  c = new int *[size];
  for(int i = 0; i < size; i++){
    c[i] = new int[size];
  }
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      c[i][j] = 0;
      for(int k = 0; k < size; k++){
	c[i][j] += a[i][j]*b[k][j];
      }
    }
  }
  return c;
}
