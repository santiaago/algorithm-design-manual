//  programming_challenges_23.cpp: santiaago
//  description: Light, More Light - 110701

#include <iostream>
#include <vector>

using namespace std;

int main(){
  cout << "Light, More Light" << endl;

  vector<bool> lights;
  string line;
  while(getline(cin, line, '\n')){

    long current_number = atol(line.c_str());
    if(current_number == 0) break;
    
    bool on(false);
    for(long i = 1; i <= current_number; i++){
      if((current_number%i) == 0){
	on = on? false: true;
      }
    }
    lights.push_back(on);
  }
  for(int i = 0; i < lights.size(); i++){
    if(lights[i]){
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
