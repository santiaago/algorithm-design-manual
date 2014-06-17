// programming_challenges_12.cpp: santiaago
// Description: The Trip: Programming challenges 110103

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;
const double kEpsilon = 0.01;

bool zeros(vector<double> v);
double pround(double x, int precision);
void printExpenses(vector<double> expenses);

int main(){
  cout << "The trip" << endl;

  unsigned int number_students(0);
  cin >> number_students;

  vector<double> expenses(number_students);  // holds trip expenses.
  double expense(0);                         // read current expense.

  // read trip expense until '0'
  unsigned int current_index_expense(0);
  while (cin >> expense && expense != 0) {
    expenses[current_index_expense] = expense;
    current_index_expense++;
  }

  double total_expenses = accumulate(expenses.begin(), expenses.end(), 0.0);
  double avg_expenses = pround(total_expenses / double(number_students), 2);

  cout << "total expenses: " << total_expenses << " avg expenses: " << avg_expenses << endl;

  printExpenses(expenses);

  vector<double> expense_distribution(expenses);  // holds the expense distribution to make for each student.

  for(int i = 0; i < number_students; i++){
    expense_distribution[i] = expense_distribution[i] - avg_expenses;
  }

  double exchange(0.0);
  // loop until the expense distribution is near zero.
  while(!zeros(expense_distribution)){//to_distribute){
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
