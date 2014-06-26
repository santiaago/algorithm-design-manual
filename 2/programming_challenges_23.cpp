//  programming_challenges_23.cpp: santiaago
//  description: Light, More Light - 110701

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

int main(){
  //cout << "Light, More Light" << endl;

  vector<bool> lights;
  string line;
  while(getline(cin, line, '\n')){

    long long current_number = atol(line.c_str());
    if(current_number == 0) break;
    long long root = sqrt(current_number);
    if((root * root) == current_number){
      lights.push_back(true);
    } else{
      lights.push_back(false);
    }
  }
  for(int i = 0; i < lights.size(); i++){
    if(lights[i]){
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
