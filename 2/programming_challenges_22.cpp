//  programming_challenges_22.cpp: santiaago
//  description: A Multiplication Game - 110505

#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

const double kEpsilon = 0.0000000001;

void computeIntervals(vector< pair<double, double> > &v1, vector< pair<double, double> > &v2, double log_number);
bool isValueComputed(const vector< pair<double, double> > &v1, const vector< pair<double, double> > &v2, double e);
int getWinner(const vector< pair<double, double> > &v1, const vector< pair<double, double> > &v2, double e);

int main(){
  vector< pair<double, double> > stan_intervals;
  vector< pair<double, double> > ollie_intervals;

  // initialization:
  stan_intervals.push_back(make_pair(log(1), log(9)));
  ollie_intervals.push_back(make_pair(log(9+1), log(9*2)));

  string line;
  while(getline(cin, line, '\n')){

    long current_number = atol(line.c_str());
    double log_number = log(current_number);
    
    if(!isValueComputed(stan_intervals, ollie_intervals, log_number)){
      computeIntervals(stan_intervals, ollie_intervals, log_number);
    }
    
    int w = getWinner(stan_intervals, ollie_intervals, log_number);
    if( w == 1){
      cout << "Stan wins." << endl;
    } else if (w == 2){
      cout << "Ollie wins." << endl;
    } else{
      cout << "error!" << endl;
    }
    
  }
}

void computeIntervals(vector< pair<double, double> > &v1, vector< pair<double, double> > &v2, double log_number){
  
  double last_interval_low1, last_interval_up1;
  double last_interval_low2, last_interval_up2;

  bool go_through = false;
  int index(0);
  while(!go_through){
    index = v1.size() - 1;
    last_interval_low1 = v1[v1.size()-1].first;
    last_interval_up1 = v1[v1.size()-1].second;
    last_interval_low2 = v2[v2.size()-1].first;
    last_interval_up2 = v2[v2.size()-1].second;
    if(last_interval_up1 < log_number && last_interval_up2 < log_number){
      double l1 = log(exp(v2[index].second)+1);
      double u1 = v2[index].second + log(9);
      v1.push_back(make_pair(l1, u1));

      double l2 = log(exp(u1)+1);
      double u2 = u1 + log(2);
      v2.push_back(make_pair(l2, u2));
    } else {
      go_through = true;
    }
  }
}

//  1 <=> vector 1
//  2 <=> vector 2
//  0 <=> not found
int getWinner(const vector< pair<double, double> > &v1, const vector< pair<double, double> > &v2, double e){

  // searching in v1
  for(int i = 0; i < v1.size(); i++){
    if( (e - v1[i].first) >= -kEpsilon && (v1[i].second - e) >= -kEpsilon ){
      return 1;
    } else {
      if( (v1[i].first - e) >= -kEpsilon){
	break;
      }
    }
  }
  // searching in v2
  for(int i = 0; i < v2.size(); i++){
    if( (e - v2[i].first) >= -kEpsilon && (v2[i].second - e) >= -kEpsilon){
      return 2;
    } else {
      if( (v2[i].first - e) >= -kEpsilon){
	break;
      }
    }
  }

  return 0;
}

bool isValueComputed(const vector< pair<double, double> > &v1, const vector< pair<double, double> > &v2, double e){
  if(v1.size() == 0 || v2.size() == 0) return false;
  
  double last_interval_low, last_interval_up;

  last_interval_low = v1[v1.size()-1].first;
  last_interval_up = v1[v1.size()-1].second;

  if(last_interval_up < e){
    last_interval_low = v2[v2.size()-1].first;
    last_interval_up = v2[v2.size()-1].second;
    if(last_interval_up < e){
      return false;
    }
  }
  return true;
}
