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
string getHighestCandidateFromMap(map<string, unsigned int> candidates);
bool areCandidatesTied(map<string, unsigned int> candidates);
void printVoteSummary(map<unsigned int, map<string, unsigned int> >candidate_votes);
void buildVoting(vector<string> &candidates, 
		 map<string, unsigned int> &map_candidate, 
		 map<unsigned int, map<string, unsigned int> > &candidate_votes, 
		 vector<vector<unsigned int> > &all_votes);

string getHighestCandidateFromLowest(unsigned int lowest_candidate, 
				     vector< vector<unsigned int> > all_votes, 
				     map< unsigned int, map<string, unsigned int> > candidate_votes,
				     map<string, unsigned int> map_candidate,
				     vector<string> candidates);

int main(){
  cout << "Australian Voting" << endl;
  unsigned int num_cases(0);
  cin >> num_cases;
  string line;
  getline (cin, line);
  vector<string> winners;
  while(num_cases > 0){

    vector<string> candidates;
    map<string, unsigned int> map_candidate;
    map<unsigned int, map<string, unsigned int> > candidate_votes;
    vector<vector<unsigned int> > all_votes;
    
    buildVoting(candidates, map_candidate, candidate_votes, all_votes);

    // look for winner
    double mayority = all_votes.size()/double(2.0);
    bool has_winner(false);

    while(!has_winner){
      // look for candidate with mayority
      for(auto t : candidate_votes[1]){
	if(t.second > mayority){
	  winners.push_back(t.first);
	  has_winner = true;
	  break;
	}
      }
      // mayority not found, remove lowest candidate.
      // search for best candidate in votes where lowest candidate was first.
      // give lowest candidate the votes of the best candidate.

      if(!has_winner){
	string lowest_candidate = getLowestCandidate(candidate_votes[1]);
	string highest_candidate = getHighestCandidateFromLowest(map_candidate[lowest_candidate], all_votes, candidate_votes, map_candidate,candidates);
	unsigned int votes_to_give = candidate_votes[1][lowest_candidate];
	map<string, unsigned int>::iterator to_remove;
	to_remove = candidate_votes[1].find(lowest_candidate);
	candidate_votes[1].erase(to_remove);
	candidate_votes[1][highest_candidate] += votes_to_give;
      }
      if(areCandidatesTied(candidate_votes[1])){
	for(auto c : candidate_votes[1]){
	  winners.push_back(c.first);
	}
	has_winner = true;
      }
    }
    num_cases--;
  }

  for(int i = 0; i < winners.size(); i++){
    cout << "winner: " << winners[i] << endl;
  }
}

void buildVoting(vector<string> &candidates, 
		 map<string, unsigned int> &map_candidate, 
		 map<unsigned int, map<string, unsigned int> > &candidate_votes, 
		 vector<vector<unsigned int> > &all_votes){
  
  unsigned int num_candidates(0);
  cin >> num_candidates;
  cin.ignore();
  
  // read candidates
  string candidate;
  while( num_candidates > 0 && getline(cin, candidate, '\n')){
    candidates.push_back(candidate);
    map_candidate[candidate] = candidates.size()-num_candidates + 1;
    num_candidates--;
  }
  
  // read up to 1000 lines    
  string vote;
  unsigned int num_votes(0);
  while( num_votes < 1000){
    getline(cin, vote, '\n');
    if(vote.empty()) break;
    istringstream stm(vote);
    unsigned int index_candidate;
    vector<unsigned int> current_vote;
    while( stm >> index_candidate){
      current_vote.push_back(index_candidate);
    }
    for(int i = 0; i < current_vote.size(); i++){
      candidate_votes[i + 1][candidates[current_vote[i]-1]]++;
    }
    num_votes++;
    all_votes.push_back(current_vote);
  }
  printVoteSummary(candidate_votes);
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

string getHighestCandidateFromLowest(unsigned int lowest_candidate, 
				     vector< vector<unsigned int> > all_votes, 
				     map< unsigned int, map<string, unsigned int> > candidate_votes, 
				     map<string, unsigned int> map_candidate,
				     vector<string> candidates){
  string highest_candidate;

  // find all votes where the lowest_candidate was vote as 1st candidate and count 2nd votes.
  map<string, unsigned int> votes;
  for(int i = 0; i < all_votes.size(); i++){
    if(all_votes[i][0] == lowest_candidate){
      votes[candidates[all_votes[i][1] - 1]]++;
    }
  }
  // for(auto v : votes){
  //   cout << v.first << " : " << v.second << endl;
  // }
  bool found(false);
  while(!found){
    highest_candidate = getHighestCandidateFromMap(votes);
    map<string, unsigned int>::iterator it;
    it = candidate_votes[1].find(highest_candidate);
    if(it != candidate_votes[1].cend()){
      found = true;
    }else{
      map<string, unsigned int>::iterator to_remove;
      to_remove = votes.find(highest_candidate);
      votes.erase(to_remove);
    }
  }
  return highest_candidate;
}

string getHighestCandidateFromMap(map<string, unsigned int> candidates){
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

void printVoteSummary(map<unsigned int, map<string, unsigned int> >candidate_votes){
    cout << "-- summary --" << endl;
    for(auto t : candidate_votes){
      cout << t.first << " | ";
      for(auto t2 : t.second){
	cout << "\t" << t2.first << " : " << t2.second << endl;
      } 
    }
}
