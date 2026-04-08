#include "factory.h"
#include <string>
#include <iostream>

using namespace std;

employee::employee(unsigned id, string name, chrono::year_month_day date_hired) 
  : id_m(id), name_m(name), date_hired_m(date_hired) {}

void employee::printEmployee(void) const
{
  cout << "Name: " << name_m 
    << "Employee Number: " << id_m
    << "Date Hired: " << date_hired_m;
}

productionWorker::productionWorker(shift shift, unsigned hr_pay, employee emp)
  : shift_m(shift), hourly_pay_m(hr_pay), employee(emp) {}

void productionWorker::printProductionWorker(void) const
{
  printEmployee(); 

  cout << "Shift: "; 
  if (shift_m == 1) cout << "Daytime";
  else cout << "Nighttime";

  cout << "Hourly Pay: " << hourly_pay_m;
}

shiftSupervisor::shiftSupervisor(
  unsigned annual_pay, unsigned bonus, employee emp)
    : annual_salary_m(annual_pay), bonus_m(bonus), employee(emp) {} 

void shiftSupervisor::printShiftSupervisor() const
{
  printEmployee();
  cout << "Annual Salary: " << annual_salary_m
    << "Bonus: " << bonus_m;
}

teamLeader::teamLeader(
  unsigned monthly_bonus, unsigned req_train_hr, 
  unsigned train_hours, productionWorker prod_worker)
    : monthly_bonus_m(monthly_bonus), req_train_hours_m(req_train_hr),
      train_hours_m(train_hours), productionWorker(prod_worker) {}

void teamLeader::printTeamLeader(void) const
{
  printProductionWorker();
  cout << "Monthly Bonus: " << monthly_bonus_m
    << "Required Training Hours: " << req_train_hours_m
    << "Completed Training Hours: " << train_hours_m;
}

