//  programming_challenges_21.cpp: santiaago
//  description: Primary Arithmetic - 110501

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int carry(char a, char b, int previous_carry);

int main(){
  cout << "Primary Arithmetic" << endl;
  bool canRead(true);

  vector<string> output;
  while(canRead){
    string line;
    getline(cin, line, '\n');
    
    istringstream stm(line);
    string current_number;
    string a = "";
    string b = "";
    int index(0);
    while(stm >> current_number){
      if(index == 0){
	a = current_number;
      } else if(index == 1){
	b = current_number;
      }
      index++;
    }
    if( a.compare("0") == 0 && b.compare("0") == 0){
      canRead = false;
      continue;
    }

    cout << "|a:" << a << "|" << endl;
    cout << "|b:" << b << "|" << endl;
    int cursor(0);
    int current_carry(0);

    int number_of_carry(0);
    for(int i = a.size() -1; i >=0; i--){
      int j = b.size() - 1 -cursor;
      cout << "a:"<< a[i] << endl;
      cout << "b:"<< b[j] << endl;
      int c  = carry(a[i], b[j], current_carry);
      if(c > 0){
	current_carry = c;
	number_of_carry++;
      } else {
	current_carry = 0;
      }
      cursor++;
    }
    if(number_of_carry ==  1){
      char phrase[50];
      sprintf(phrase, "%d carry operation.", number_of_carry);
      output.push_back(phrase);
    } else if (number_of_carry == 0){
      output.push_back("No carry operation.");
    } else { 
      char phrase[50];
      sprintf(phrase, "%d carry operations.", number_of_carry);
      output.push_back(phrase);
    }
  }
  for(int i = 0; i < output.size(); i++){
    cout << output[i] << endl;
  }
  cout << "end" << endl;
}

int carry(char a, char b, int previous_carry){
      int ia, ib;
      ia = a - '0';
      ib = b - '0';
      if(previous_carry + ia + ib > 9){
        return 1;//(previous_carry + ia + ib -9);
      }
      return 0;
}
