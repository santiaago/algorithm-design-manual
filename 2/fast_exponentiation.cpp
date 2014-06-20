//  fast_exponentiation.cpp: santiaago
//  Description: power algorithm in log n time.

#include <iostream>

using namespace std;

long power(long a, long n);

int main(){
  cout << "fast exponentitation" << endl;
  cout << "2 ^2 = " << power(2,2) <<endl;
  cout << "2 ^3 = " << power(2,3) <<endl;
}

long power(long a, long n){
  if(n == 0){
    return 1;
  }
  long t = power(a, n/2);
  if(n%2 == 0){
    return t * t;
  } else {
    return t * t * a;
  }
}
