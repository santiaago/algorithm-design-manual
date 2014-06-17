// programming_challenges_12.cpp: santiaago
// Description: The Trip: Programming challenges 110103

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;
double kEpsilon = 0.001;

bool zeros(vector<double> v);
double pround(double x, int precision);

int main(){
  cout << "The trip" << endl;
  unsigned int number_students(0);
  cin >> number_students;
  vector<double> expenses(number_students);
  double expense(0);
  int count(0);
  while (cin >> expense && expense != 0) {
    expenses[count] = expense;
    count++;
  }
  double total_expenses = accumulate(expenses.begin(), expenses.end(), 0.0);
  double avg_expenses = pround(total_expenses / double(number_students), 2);
  cout << "total expenses: " << total_expenses << " avg expenses: " << avg_expenses << endl;
  for(int i = 0 ; i < number_students ; i++){
    cout << expenses[i] << " | ";
  }
  cout << endl;
  vector<double> expense_distribution(expenses);
  for(int i = 0; i < number_students; i++){
    expense_distribution[i] = expense_distribution[i] - avg_expenses;
  }
  for(int i = 0 ; i < number_students ; i++){
    cout << expense_distribution[i] << " | ";
  }
  cout<< endl;
  bool to_distribute = true;
  double exchange(0.0);
  int index(0);
  while(to_distribute){
    cout << " -- " << endl;
    for(int i = 0 ; i < number_students ; i++){
      cout << expense_distribution[i] << " | ";
    }
    cout << endl;
    while(expense_distribution[index] >= 0 && index < number_students){
      index++;
    }
    if(index >= number_students){
      break;
    }
    cout << "current index " << index << endl;
    cout << "selected distribution: " << expense_distribution[index] << endl;

    for(int i = 0; i < number_students; i++){
      if(expense_distribution[i] > kEpsilon){
	double rest = expense_distribution[i] + expense_distribution[index];
	if( rest < -kEpsilon){
	  exchange += abs(expense_distribution[i]);
	  expense_distribution[i] = 0;
	  expense_distribution[index] = rest;
	} else if(rest > kEpsilon){
	  exchange += abs(expense_distribution[index]);
	  expense_distribution[i] = rest;
	  expense_distribution[index] = 0;
	} else {
	  exchange += abs(expense_distribution[index]);	  
	  expense_distribution[i] = 0;
	  expense_distribution[index] = 0;
	}
	cout << "current exchange: " << exchange << endl;
	break;
      }
    }
    index = 0;
    to_distribute = !zeros(expense_distribution);
  }
  cout << "amount exchanged: " << exchange << endl;
  for(int i = 0 ; i < number_students ; i++){
    cout << expense_distribution[i] << " | ";
  }
  cout << endl;
}

bool zeros(vector<double> v){
  for(double i : v){
    if(abs(i) > kEpsilon){
      return false;
    }
  }
  return true;
}


double pround(double x, int precision)
{
  if (x == 0.){
    return x;
  }
  int ex = floor(log10(abs(x))) - precision + 1;
  double div = pow(10, ex);
  return floor(x / div + 0.5) * div;
}

