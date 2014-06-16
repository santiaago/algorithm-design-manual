// 128.cpp: santiaago
// Description: Write a function to perform integer division without using either the / or * operators. Find a fast way to do it.

#include <iostream>

using namespace std;

int Division(int numerator, int denominator){
  int quotient(0);
  while(numerator >= denominator){
    numerator = numerator - denominator;
    quotient++;
  }
  return quotient;
}

int main(){
  cout << "Write a function to perform integer division without using either the / or * operators. Find a fast way to do it." << endl;
  for(int i = 10; i > 0; i --){
    cout << 42 << " / " << i << " = " << Division(42, i) << endl;
  }
}
