// programming_challenges_11.cpp: santiaago
// Description: The 3n + 1 problem: Programming challenges 110101

#include <iostream>
#include <vector>

using namespace std;

unsigned int sizeOfThreeNPlusOne(int n){
  vector<int> sequence;
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

unsigned int maxCycleLength(int i, int j){
  unsigned int max_cycle_lenght(0);
  for(; i <= j; i++){
    unsigned int k = sizeOfThreeNPlusOne(i);
    if(k > max_cycle_lenght){
      max_cycle_lenght = k;
    }
  }
  return max_cycle_lenght;  
}

int main(){
  cout << "The 3n + 1 problem" << endl;
  cout << "size of sequence of 10 is: " << sizeOfThreeNPlusOne(10) << endl; 
  cout << "i: " << 1 << " j: " << 10 << " maximum cycle lenght " << maxCycleLength(1, 10) << endl;
  cout << "i: " << 100 << " j: " << 200 << " maximum cycle lenght " << maxCycleLength(100, 200) << endl;  
  cout << "i: " << 201 << " j: " << 210 << " maximum cycle lenght " << maxCycleLength(201, 210) << endl;
  cout << "i: " << 900 << " j: " << 1000 << " maximum cycle lenght " << maxCycleLength(900, 1000) << endl;
  cout << "i: " << 999998 << " j: " << 1000000 << " maximum cycle lenght " << maxCycleLength(999998, 1000000) << endl;

}
