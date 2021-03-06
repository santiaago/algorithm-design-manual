// programming_challenges_12.cpp: santiaago
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
double pround(double x, int precision);
void printExpenses(vector<double> expenses);
double totalExchangedToEqualize(vector<double> expenses);

int main(){
  cout << "The trip" << endl;

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
  for(double e : exchanged){
    cout << "$"  << fixed << setprecision(2) << e/double(100.0) << endl;
  }
}

double totalExchangedToEqualize(vector<double> expenses){
  unsigned int number_students(expenses.size());
  
  double total_expenses = accumulate(expenses.begin(), expenses.end(), 0.0);
  double avg_expenses;
  modf(round(total_expenses / double(number_students)) , &avg_expenses);

  cout << "total expenses: " << total_expenses << " avg expenses: " << avg_expenses << endl;

  printExpenses(expenses);

  vector<double> expense_distribution(expenses);  // holds the expense distribution to make for each student.

  for(int i = 0; i < number_students; i++){
    expense_distribution[i] = expense_distribution[i] - avg_expenses;
  }

  double exchange(0.0);
  // loop until the expense distribution is near zero.
  while(!zeros(expense_distribution)){
    printExpenses(expense_distribution);

    int index(0);  // index of first negative expense.
    // this is <=> to first student that needs to give back money as he did not gave enough.
    while(expense_distribution[index] >= 0 && index < number_students){
      index++;
    }
    if(index >= number_students){ // did not find any student that needs to give back money. We are done.
      break;
    }

    cout << "current index " << index << endl;
    cout << "selected distribution: " << expense_distribution[index] << endl;
    
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
	cout << "current exchange: " << exchange << endl;
	found = true;
	break;
      }
    }
    if(!found){
      break;
    }
  }

  cout << "amount exchanged: " << exchange << endl;
  printExpenses(expense_distribution);
  return exchange;
}

bool zeros(vector<double> v){
  for(double i : v){
    if(abs(i) > kEpsilon){
      return false;
    }
  }
  return true;
}

// Round double to a given precision.
// From http://stackoverflow.com/questions/11208971/round-a-float-to-a-given-precision/
double pround(double x, int precision)
{
  if (x == 0.){
    return x;
  }
  int ex = floor(log10(abs(x))) - precision + 1;
  double div = pow(10, ex);
  return floor(x / div + 0.5) * div;
}

// Print vector of expenses in the following format.
// 1.00 | 2.00 | 3.01 |
void printExpenses(vector<double> expenses){
  unsigned int num(expenses.size());
  for(int i = 0 ; i < num ; i++){
    cout << expenses[i] << " | ";
  }
  cout << endl;
}
