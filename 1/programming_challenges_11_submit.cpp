// programming_challenges_11.cpp: santiaago
// Description: The 3n + 1 problem: Programming challenges 110101

#include <iostream>
#include <vector>

using namespace std;

unsigned int sizeOfThreeNPlusOne(unsigned long n);
unsigned int maxCycleLength(unsigned long i, unsigned long j);

int main(){
  long i, j;
  while (cin >> i >> j) {
    cout << i << " " << j << " " << maxCycleLength(min(i,j), max(i,j)) << endl;
  }
}

unsigned int sizeOfThreeNPlusOne(unsigned long n){
  vector<long> sequence;
  while( n != 1 ) {
    sequence.push_back(n);
    if( n % 2 == 0 ) {
      n = n / 2;
    } else {
      n = n * 3 + 1;
    }
  }
  sequence.push_back(1);
  return sequence.size();  
}

unsigned int maxCycleLength(unsigned long i, unsigned long j){
  unsigned int max_cycle_lenght(0);
  for(; i <= j; i++){
    unsigned long k = sizeOfThreeNPlusOne(i);
    if(k > max_cycle_lenght){
      max_cycle_lenght = k;
    }
  }
  return max_cycle_lenght;  
}
