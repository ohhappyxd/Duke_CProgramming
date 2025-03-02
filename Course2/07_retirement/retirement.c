#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
  typedef struct _retire_info retire_info;
double compute_balance(int age, double balance, retire_info retire){
  printf("Age %3d month %2d you have $%.2f\n", age/12, age%12, balance);
  balance = balance + balance * retire.rate_of_return + retire.contribution;
  return balance;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int age = startAge;
  double balance = initial;
  for (int i = 0; i < working.months; i++) {
    balance = compute_balance(age, balance, working);
    age++;
  }
  for (int i = 0; i < retired.months; i++) {
    balance = compute_balance(age, balance, retired);
    age++;
  }
}

int main(void){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
