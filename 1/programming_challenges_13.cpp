// programming_challenges_13.cpp: santiaago
// Description: Australian Voting - Programming challenges 110108

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
void printVector(vector<T> v);

int main(){
  cout << "Australian Voting" << endl;
  unsigned int num_cases(0);
  cin >> num_cases;
  string line;
  getline (cin, line);
  while(num_cases > 0){
    unsigned int num_candidates(0);
    cin >> num_candidates;
    vector<string> candidates(num_candidates);
    string candidate;
    while( num_candidates > 0 && cin >> candidate ){
      candidates[candidates.size()-num_candidates] = candidate;
      num_candidates--;
    }
    printVector(candidates);
    // read up to 1000 lines
    string vote;
    unsigned int num_votes(0);
    cin.ignore();
    while( num_votes < 1000){
      getline(cin, vote);
      if(vote.empty()) break;
      istringstream stm(vote);
      unsigned int index_candidate;
      vector<unsigned int> current_vote;
      while( stm >> index_candidate){
	current_vote.push_back(index_candidate);
      }
      printVector(current_vote);
      num_votes++;
    }
    cout << "case done " << endl;
    num_cases--;
  }
  cout << "end" << endl;
}

template<typename T>
void printVector(vector<T> v){
  for(T c : v){
    cout << c << " | ";
  }
  cout << endl;
}
