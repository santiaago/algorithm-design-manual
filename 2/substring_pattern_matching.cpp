// substring_pattern_matching.cpp: santiaago
// Description: substring pattern matching. 
//              A text string t and a pattern string p. Doest t contains the pattern p as a substring and if so where.

#include <iostream>

using namespace std;

int find_substring(string t, string p);
int find_substring_ex(string t, string p);

int main(){
  cout << "substring pattern matching" << endl;
  string t = "At the request of the moon";
  string p1 = "moon";
  string p2 = "the";
  string p3 = "thee";
  cout << "substring pattern '" << p1 << "' position in '" << t << "' : " << find_substring(t, p1) << endl;
  cout << "substring pattern '" << p2 << "' position in '" << t << "' : " << find_substring(t, p2) << endl;
  cout << "substring pattern '" << p3 << "' position in '" << t << "' : " << find_substring(t, p3) << endl;

  cout << "substring pattern '" << p1 << "' position in '" << t << "' : " << find_substring_ex(t, p1) << endl;
  cout << "substring pattern '" << p2 << "' position in '" << t << "' : " << find_substring_ex(t, p2) << endl;
  cout << "substring pattern '" << p3 << "' position in '" << t << "' : " << find_substring_ex(t, p3) << endl;
  
}

int find_substring(string t, string p){
  int pattern_cursor(0);
  int position(-1);

  for(int i = 0; i < t.size(); i++){
    if(t[i] == p[pattern_cursor]){
      pattern_cursor++;
      if(position == -1){
	position = i;
      }
    } else{
      pattern_cursor = 0;
      position = -1;
    }
    if(pattern_cursor ==  p.size()){
      break;
    }
  }
  if(pattern_cursor == p.size()){
    return position;
  } else{
    return -1;
  }
}

int find_substring_ex(string t, string p){
  int i,j;
  int n, m;
  n = t.size();
  m = p.size();

  for(int i = 0; i <= (n - m); i++){
    j = 0;
    while( j < m && t[i+j] == p[j]){
      j++;
    }
    if(j == m){
      return i;
    }
  }
  return -1;
}
