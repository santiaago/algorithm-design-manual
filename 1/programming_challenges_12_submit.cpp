// programming_challenges_12_submit.cpp: santiaago
// Description: The Trip: Programming challenges 110103

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;
const double kEpsilon = 0.01;

bool zeros(vector<double> v);
double totalExchangedToEqualize(vector<double> expenses);

int main(){

  unsigned int number_students(0);
  vector<double> exchanged;
  while(cin >> number_students && number_students != 0){
    vector<double> expenses(number_students);  // holds trip expenses.
    double expense(0.0);                       // read current expense.
    // read trip expense until '0'
    unsigned int current_index_expense(0);
    while (number_students > 0 && cin >> expense) {
      expenses[current_index_expense] = expense*100;
      current_index_expense++;
      number_students--;
    }
    exchanged.push_back(totalExchangedToEqualize(expenses));
  }
  for(int i = 0; i < exchanged.size(); i++){
    cout << "$"  << fixed << setprecision(2) << exchanged[i]/double(100.0) << endl;
  }
}

double totalExchangedToEqualize(vector<double> expenses){
  unsigned int number_students(expenses.size());
  
  double total_expenses = accumulate(expenses.begin(), expenses.end(), 0.0);
  double avg_expenses;
  modf(total_expenses / double(number_students) , &avg_expenses);

  vector<double> expense_distribution(expenses);  // holds the expense distribution to make for each student.

  for(int i = 0; i < number_students; i++){
    expense_distribution[i] = expense_distribution[i] - avg_expenses;
  }

  double exchange(0.0);
  // loop until the expense distribution is near zero.
  while(!zeros(expense_distribution)){
    int index(0);  // index of first negative expense.
    while(expense_distribution[index] >= 0 && index < number_students){
      index++;
    }
    if(index >= number_students){ // did not find any student that needs to give back money. We are done.
      break;
    }
    
    // search in all students the first one that needs to get back some money as he gave too much.
    bool found(false);
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
	found = true;
	break;
      }
    }
    if(!found){
      break;
    }
  }
  return exchange;
}

bool zeros(vector<double> v){
  for(int i = 0 ; i < v.size(); i++){
    if(abs(v[i]) > kEpsilon){
      return false;
    }
  }
  return true;
}
