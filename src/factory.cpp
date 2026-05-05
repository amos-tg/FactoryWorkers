#include "factory.h"
#include <string>
#include <iostream>
#include <format>

using namespace std;

employee::employee(unsigned id, string name, chrono::year_month_day date_hired) 
  : name_m(name), date_hired_m(date_hired) 
{
  if (isIdValid(id))
    id_m = id;
  else 
    throw invalidEmployeeNumber(id);
}

void employee::setId(unsigned id)
{
  if (isIdValid(id))
    id_m = id;
  else 
    throw invalidEmployeeNumber(id);
}

bool isIdValid(unsigned id)
{
  if (id < 0 || id > 9999)
    return false;
  else
    return true;
}

void employee::printEmployee(void) const
{
  // print all the employee data members 
  cout << "Name: " << name_m << '\n'
    << "Employee Number: " << id_m << '\n'
    << "Date Hired: " << date_hired_m << endl;
}

invalidEmployeeNumber::invalidEmployeeNumber(unsigned emp_id) 
  : id_m(emp_id), msg(
    format("Error: invalidEmployeeNumber: {}, out of range [0,9999]", emp_id)) {}

productionWorker::productionWorker(shift shift, unsigned hr_pay, employee emp)
  : shift_m(shift), hourly_pay_m(hr_pay), employee(emp) {}

void productionWorker::printProductionWorker(void) const
{
  printEmployee(); 

  // convert the shift enum to a string and print
  cout << "Shift: "; 
  if (shift_m == 1) cout << "Daytime";
  else cout << "Nighttime";
  cout << '\n';
  
  cout << "Hourly Pay: " << hourly_pay_m << endl;
}

shiftSupervisor::shiftSupervisor(
  unsigned annual_pay, unsigned bonus, employee emp)
    : annual_salary_m(annual_pay), bonus_m(bonus), employee(emp) {} 

void shiftSupervisor::printShiftSupervisor() const
{
  printEmployee();

  // print all the shiftSupervisor data
  cout << "Annual Salary: " << annual_salary_m << '\n'
    << "Bonus: " << bonus_m << endl;
}

teamLeader::teamLeader(
  unsigned monthly_bonus, unsigned req_train_hr, 
  unsigned train_hours, productionWorker prod_worker)
    : monthly_bonus_m(monthly_bonus), req_train_hours_m(req_train_hr),
      train_hours_m(train_hours), productionWorker(prod_worker) {}

void teamLeader::printTeamLeader(void) const
{
  printProductionWorker();

  // prints all the production worker related data
  cout << "Monthly Bonus: " << monthly_bonus_m << '\n'
    << "Required Training Hours: " << req_train_hours_m << '\n'
    << "Completed Training Hours: " << train_hours_m << endl;
}
