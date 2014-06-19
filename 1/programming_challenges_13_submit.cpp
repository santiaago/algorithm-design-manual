// programming_challenges_13.cpp: santiaago
// Description: Australian Voting - Programming challenges 110108

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <limits> // max
#include <algorithm> // find

using namespace std;

typedef vector<string> CandidatesVector;
typedef map<string, unsigned int> CandidatesVoteMap;
typedef map<string, unsigned int> CandidatesPositionMap;
typedef map<unsigned int, CandidatesVoteMap> VotingMap;
typedef vector<unsigned int > VoteVector;
typedef vector<VoteVector> VotesVector;
typedef vector< CandidatesVector > WinnersByCaseVector;
typedef vector<CandidatesVector >  CandidatesByCaseVector;

bool areCandidatesTied(const CandidatesVoteMap &candidates);

void getLowestCandidates(const CandidatesVoteMap &candidates, CandidatesVector &lowest_candidates);
string getHighestCandidateFromMap(const CandidatesVoteMap &candidates);
string getHighestCandidateFromLowest(const unsigned int lowest_candidate, const CandidatesVector &lowest_candidates, const VotesVector all_votes, VotingMap candidate_votes, const CandidatesVector candidates, const CandidatesVector &eliminated_candidates);

void buildVoting(CandidatesVector &candidates, CandidatesPositionMap &candidates_position, VotingMap &candidate_votes, VotesVector &all_votes);
void addWinners(CandidatesVector &winners, const VotesVector &all_votes, VotingMap &candidate_votes, const CandidatesPositionMap &map_candidate, const CandidatesVector &candidates);

int main(){
  // ready number of cases.
  unsigned int num_cases(0);
  cin >> num_cases;

  // ready empty line.
  string line;
  getline (cin, line);

  WinnersByCaseVector winners(num_cases);    // container to hold the winners of each case / election.
  CandidatesByCaseVector all_candidates(num_cases);
  while(num_cases > 0){

    CandidatesVector candidates;                // vector of candidate names.
    CandidatesPositionMap candidates_position;  // map of each candidate position from 1st to nth.
    VotingMap candidate_votes;                  // map of all positions in current election, and for each position the number of votes of each candidate.
    VotesVector all_votes;                      // vector that has all votes in current election
    // fill all containers by reading the input stream.
    buildVoting(candidates, candidates_position, candidate_votes, all_votes);
    
    // append winners to collection based of the votes.
    addWinners(winners[winners.size() - num_cases], all_votes, candidate_votes, candidates_position, candidates);
    all_candidates[all_candidates.size() - num_cases] = candidates;
    num_cases--;
  }

  // print winners, one by line, and a blank line per case.
  // print winners in the same order of the inputs.
  for(int i = 0; i < winners.size(); i++){
    for(int k = 0; k < all_candidates[i].size(); k++){
      for(int j = 0; j < winners[i].size(); j++){
	if(winners[i][j] == all_candidates[i][k]){
	  cout << winners[i][j] << endl;
	}
      }
    }
    if(i != winners.size() - 1){
      cout << endl;
    }
  }
}

// Fill the containers based on the input stream.
void buildVoting(CandidatesVector &candidates, CandidatesPositionMap &candidates_position, VotingMap &candidate_votes, VotesVector  &all_votes){
  
  unsigned int num_candidates(0);
  cin >> num_candidates;
  cin.ignore();
  
  // read candidates
  string candidate;
  unsigned int candidate_index(0);
  while( candidate_index < num_candidates && getline(cin, candidate, '\n')){
    candidates.push_back(candidate);
    candidates_position[candidate] = candidate_index + 1;
    candidate_index++;
  }
  
  // read up to 1000 lines    
  string vote;
  unsigned int num_votes(0);
  while( num_votes < 1000){
    getline(cin, vote, '\n');
    if(vote.empty()) break;

    istringstream stm(vote);
    unsigned int index_candidate;
    VoteVector current_vote;

    while( stm >> index_candidate){
      current_vote.push_back(index_candidate);
    }

    for(int i = 0; i < current_vote.size(); i++){
      candidate_votes[i + 1][candidates[current_vote[i]-1]]++;
    }

    num_votes++;
    all_votes.push_back(current_vote);
  }
}

// Append winners to 'winners' vector based on votes.
// Rules are as follows:
//   Initially only the first choices are counted, and if one candidate receives more than 50% of the vote then that candidate is elected. 
//   However, if no candidate receives more than 50%, all candidates tied for the lowest number of votes are eliminated. 
//   Ballots ranking these candidates first are recounted in favor of their highest-ranked non-eliminated candidate. 
//   This process of eliminating the weakest candidates and counting their ballots in favor of the preferred non-eliminated candidate 
//   continues until one candidate receives more than 50% of the vote, or until all remaining candidates are tied.
void addWinners(CandidatesVector &winners, const VotesVector &all_votes, VotingMap &candidate_votes, const CandidatesPositionMap &candidates_position,const CandidatesVector &candidates){

  double mayority = all_votes.size()/double(2.0);
  bool has_winner(false);
  CandidatesVector eliminated_candidates;

  if(all_votes.size() == 0){  // no votes <=> all candidates are winners
    for(unsigned int i = 0; i < candidates.size(); i++){
      winners.push_back(candidates[i]);
    }
    has_winner = true;
  }
  
  while(!has_winner){
    // look for candidate with mayority
    for(CandidatesVoteMap::iterator c = candidate_votes[1].begin(); c != candidate_votes[1].end(); c++){
      if(c->second > mayority){
	winners.push_back(c->first);
	has_winner = true;
	break;
      }
    }
    if(has_winner){
      break;
    }

    // mayority not found, remove lowest candidate.
    // search for best candidate in votes where lowest candidate was first.
    // give lowest candidate the votes of the best candidate.    
    if(!has_winner){
      CandidatesVector lowest_candidates;
      getLowestCandidates(candidate_votes[1], lowest_candidates);
      
      if(lowest_candidates.size() < candidate_votes[1].size()){
	for(CandidatesVector::const_iterator lowest_candidate = lowest_candidates.begin(); lowest_candidate != lowest_candidates.end(); lowest_candidate++){
	
	  CandidatesPositionMap::const_iterator lowest = candidates_position.find(*lowest_candidate);
	  if(lowest == candidates_position.end()){
	    continue;
	  }
	  string highest_candidate = getHighestCandidateFromLowest(lowest->second, lowest_candidates, all_votes, candidate_votes, candidates, eliminated_candidates);
	  unsigned int votes_to_give = candidate_votes[1][*lowest_candidate];
	  CandidatesVoteMap::iterator to_remove;
	  to_remove = candidate_votes[1].find(*lowest_candidate);
	  if(to_remove == candidate_votes[1].end()){
	    continue;
	  }
	  candidate_votes[1].erase(to_remove);
	  candidate_votes[1][highest_candidate] += votes_to_give;
	  eliminated_candidates.push_back(*lowest_candidate);
	}
      }
    }

    // if candidates in first position are all tied, they are all winners.
    if(areCandidatesTied(candidate_votes[1])){
      for(CandidatesVoteMap::iterator c = candidate_votes[1].begin(); c != candidate_votes[1].end(); c++){
	winners.push_back(c->first);
      }
      has_winner = true;
    }
  }
}

// From a map of candidate votes, fill a vector with all the lowest candidates in map.
void getLowestCandidates(const CandidatesVoteMap &candidates, CandidatesVector &lowest_candidates){
  // get minimum vote
  unsigned int min(numeric_limits<int>::max());
  for(CandidatesVoteMap::const_iterator c = candidates.begin(); c != candidates.end(); c++){
    if(c->second < min){
      min = c->second;
    }
  }
  // get candidate with minimum vote
  for(CandidatesVoteMap::const_iterator c = candidates.begin(); c != candidates.end(); c++){
    if(c->second == min){
      lowest_candidates.push_back(c->first);
    }
  }
}

// Based on the id of the lowest candidate:
//   Find the votes made to that candidates.
//   From those votes, find the best existing candidate other than the lowest.
//   Return that candidate.
string getHighestCandidateFromLowest(const unsigned int lowest_candidate, const CandidatesVector &lowest_candidates, const VotesVector all_votes, VotingMap candidate_votes, const CandidatesVector candidates, const CandidatesVector &eliminated_candidates){
  
  string highest_candidate;

  // find all votes where the lowest_candidate was vote as 1st candidate and count 2nd votes.
  CandidatesVoteMap votes;
  for(int i = 0; i < all_votes.size(); i++){
    if(all_votes[i][0] == lowest_candidate){
      // look for next non eliminated candidate.
      bool lowest_candidate_found(false);
      unsigned int candidate_index(1);  // starts at 1 as we are looking for the next non eliminated candidate in the current vote.
      while(!lowest_candidate_found){
	// look if next candidate is part of the lowest_candidates.
	CandidatesVector::const_iterator lc =  find(lowest_candidates.begin(), lowest_candidates.end(), candidates[all_votes[i][candidate_index] - 1]);
	CandidatesVector:: const_iterator old_lc = find(eliminated_candidates.begin(), eliminated_candidates.end(), candidates[all_votes[i][candidate_index] - 1]);	
	CandidatesVoteMap::iterator in_first = candidate_votes[1].find(candidates[all_votes[i][candidate_index] - 1]);
	if(lc == lowest_candidates.end() && old_lc == eliminated_candidates.end() && in_first != candidate_votes[1].end()){
	  votes[candidates[all_votes[i][candidate_index] - 1]]++;
	  lowest_candidate_found = true;
	}
	candidate_index++;
      }
    }
  }
  bool found(false);
  while(!found){
    highest_candidate = getHighestCandidateFromMap(votes);
    CandidatesVoteMap::iterator it;
    it = candidate_votes[1].find(highest_candidate);
    if(it != candidate_votes[1].end()){
      found = true;
    }else{
      CandidatesVoteMap::iterator to_remove;
      to_remove = votes.find(highest_candidate);
      votes.erase(to_remove);
    }
  }
  return highest_candidate;
}

// From a map of candidate votes, return the candidate with the highest votes.
string getHighestCandidateFromMap(const CandidatesVoteMap &candidates){
  string highest_candidate;
  unsigned int max(0);
  for(CandidatesVoteMap::const_iterator c = candidates.begin(); c != candidates.end(); c++){
    if(c->second > max){
      max = c->second;
      highest_candidate = c->first;
    }
  }
  return highest_candidate;
}

// Determine whether all candidates are tied in votes or not based on the candidates votes.
bool areCandidatesTied(const CandidatesVoteMap &candidates){
  unsigned int value(-1);
  for(CandidatesVoteMap:: const_iterator c = candidates.begin(); c != candidates.end(); c++){
    if(value == -1){
      value = c->second;
    } else {
      if(value != c->second){
	return false;
      }
    }
  }
  return true;
}
