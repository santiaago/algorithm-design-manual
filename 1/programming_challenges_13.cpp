// programming_challenges_13.cpp: santiaago
// Description: Australian Voting - Programming challenges 110108

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

template<typename T>
void printVector(vector<T> v);
void printMap(map<string, unsigned int> m);
string getLowestCandidate(map<string, unsigned int> candidates);
string getHighestCandidate(map<string, unsigned int> m);
bool areCandidatesTied(map<string, unsigned int> candidates);

int main(){
  cout << "Australian Voting" << endl;
  unsigned int num_cases(0);
  cin >> num_cases;
  string line;
  getline (cin, line);
  vector<string> winners;
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
    for(auto t : candidate_votes){
      cout << t.first << " | ";
      for(auto t2 : t.second){
	cout << "\t" << t2.first << " : " << t2.second << endl;
      } 
    }
    double mayority = num_votes/double(2.0);
    bool has_winner(false);
    while(!has_winner){
      for(auto t : candidate_votes[1]){
	if(t.second > mayority){
	  winners.push_back(t.first);
	  has_winner = true;
	  break;
	}
      }
      if(!has_winner){
	string highest_candidate = getHighestCandidate(candidate_votes[1]);
	string lowest_candidate = getLowestCandidate(candidate_votes[1]);
	unsigned int votes = candidate_votes[1][lowest_candidate];
	map<string, unsigned int>::iterator to_remove;
	to_remove = candidate_votes[1].find(lowest_candidate);
	candidate_votes[1].erase(to_remove);
	candidate_votes[1][highest_candidate] += votes;
      }
      if(areCandidatesTied(candidate_votes[1])){
	for(auto c : candidate_votes[1]){
	  winners.push_back(c.first);
	}
	has_winner = true;
      }
    }
    
    for(auto w : winners){
      cout << w << endl;
    }
    cout << "case done " << endl;
    num_cases--;
  }
  for(int i = 0; i < winners.size(); i++){
    cout << winners[i] << endl;
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

bool areCandidatesTied(map<string, unsigned int> candidates){
  unsigned int value(-1);
  for(auto c : candidates){
    if(value == -1){
      value = c.second;
    } else {
      if(value != c.second){
	return false;
      }
    }
  }
  return true;
}

string getLowestCandidate(map<string, unsigned int> candidates){
  string lowest_candidate;
  unsigned int min(numeric_limits<int>::max());
  for(auto c : candidates){
    if(c.second < min){
      min = c.second;
      lowest_candidate = c.first;
    }
  }
  return lowest_candidate;
  
}

string getHighestCandidate(map<string, unsigned int> candidates){
  string highest_candidate;
  unsigned int max(0);
  for(auto c : candidates){
    if(c.second > max){
      max = c.second;
      highest_candidate = c.first;
    }
  }
  return highest_candidate;
}
