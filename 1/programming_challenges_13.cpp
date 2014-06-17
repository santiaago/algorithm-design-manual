// programming_challenges_13.cpp: santiaago
// Description: Australian Voting - Programming challenges 110108

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

using namespace std;

template<typename T>
void printVector(vector<T> v);
void printMap(map<string, unsigned int> m);

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
    map<unsigned int, map<string, unsigned int> > candidate_votes;

    string candidate;
    while( num_candidates > 0 && cin >> candidate ){
      candidates[candidates.size()-num_candidates] = candidate;
      num_candidates--;
    }
    printVector(candidates);
    //printMap(candidate_votes);
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
      for(int i = 0; i < current_vote.size(); i++){
      	//candidate_votes[candidates[current_vote[i] - 1]]++;
	cout << "vote: " << current_vote[i] << endl;
	cout << "candidate: " << candidates[current_vote[i]-1] << endl;
	cout << "count: " << candidate_votes[i + 1][candidates[current_vote[i]-1]] << endl;
	candidate_votes[i + 1][candidates[current_vote[i]-1]]++;//candidates[current_vote[i]][
	cout << "count: " << candidate_votes[i + 1][candidates[current_vote[i]-1]] << endl;
      }
      printVector(current_vote);
      num_votes++;
    }
    // printMap(candidate_votes);
    for(auto t : candidate_votes){
      cout << t.first << " | ";
      for(auto t2 : t.second){
	cout << "\t" << t2.first << " : " << t2.second << endl;
      } 
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

void printMap(map<string, unsigned int> m){
  for(auto t : m){
    cout << t.first << " : " << t.second << endl;
  }
}
