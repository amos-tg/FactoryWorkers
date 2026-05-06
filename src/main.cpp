#include "factory.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

void newEmployee(void);

employee addEmployee(void);

productionWorker addProdWorker(void);

shiftSupervisor addShiftSupervisor(void);

teamLeader addTeamLeader(void);

void sscroll(void);

const string main_menu = 
R"(Factory Employee Manager:
  1) New Employee
  
  2) Exit

  (input 1 or 2) : )";

// exit is defined in multiple menus so namespacing from enum class is needed
enum class menuOpt { NEW = 1, PRINT, EXIT };

int main(void) 
{
  while (true) 
  {
    unsigned opt;

    sscroll();
    cout << main_menu;
    cout.flush();
    cin >> opt;

    if (!cin) 
    {
      cin.ignore().clear();
      continue;
    }

    switch (static_cast<menuOpt>(opt))
    {
    case menuOpt::NEW:
      newEmployee();
      break;

    case menuOpt::EXIT:
      exit(EXIT_SUCCESS);

    default:
      continue;        
    }
  }
}

const char* emp_type_menu =
R"(Pick Employee Type to be Added:
  1) Production Worker
  2) Shift Supervisor
  3) Team Leader

  4) Exit

  (input 1-4): )";

enum class employeeType 
{ 
  PRODUCTION_WORKER, SHIFT_SUPERVISOR,
  TEAM_LEADER, EXIT
};

void newEmployee(void)
{
  while (true)
  {
    unsigned opt;

    sscroll();
    cout << emp_type_menu;  
    cout.flush();

    cin >> opt;

    if (!cin)
    {
      cin.ignore().clear();
      continue;
    }

    switch (static_cast<employeeType>(opt))
    {
    case employeeType::PRODUCTION_WORKER:
      addProdWorker().printProductionWorker();
      return;

    case employeeType::SHIFT_SUPERVISOR:
      addShiftSupervisor().printShiftSupervisor();
      return;

    case employeeType::TEAM_LEADER:
      addTeamLeader().printTeamLeader();
      return;

    case employeeType::EXIT:
      exit(EXIT_SUCCESS);

    default:
      continue;
    }
  }
}

/// T is the type queried for
template<typename T>
T query(const char* msg)
{
  T opt;
  while (true)
  {
    cout << msg;
    cout.flush();

    cin >> opt;
    if (!cin)
    {
      cin.ignore().clear();
      continue;
    }
    else 
    {
      cout << endl;
      return opt;
    }
  }
}

employee addEmployee(void) 
{
  employee emp {};

  sscroll();

  while (true)
  {
    try 
    {
      emp.setId(query<unsigned>("Input Employee Id (Numeric): "));
    }
    catch (const invalidEmployeeNumber& err)
    {
      cerr << err.what() << endl;
      continue;
    }

    break;
  }

  string name { query<string>("Input Employee Name: ") };
  emp.setName(name);

  chrono::day day { 
    query<unsigned>("Input Employee Hiring Date Day Number: ") };

  chrono::year year { 
    query<int>("Input Employee Hiring Date Year Number: ") };
  
  chrono::month month { 
    query<unsigned>("Input Employee Hiring Date Month Number: ") };

  chrono::year_month_day ymd { year, month, day };
  emp.setDateHired(ymd);

  return emp;
}

productionWorker addProdWorker(void)
{
  employee emp { addEmployee() };
  productionWorker pr_wkr { emp };

  while (true)
  {
    try 
    {
      productionWorker::shift shift {
        static_cast<productionWorker::shift>(
          query<unsigned>("Input Employee Shift, (Day=1 or Night=2): ")) };

      pr_wkr.setShift(shift);
    } 
    catch (const invalidShift& err) 
    {
      cerr << err.what() << endl;
      continue;
    }

    break;
  }

  while (true)
  {
    try
    {
      unsigned hr_pay {
        query<unsigned>("Input Employee Hourly Pay: ") };

      pr_wkr.setHourlyPay(hr_pay);
    }
    catch (const invalidPayRate& err)
    {
      cerr << err.what() << endl;
      continue;
    }

    break;
  }

  return pr_wkr;
}

shiftSupervisor addShiftSupervisor(void)
{
  sscroll();   

  employee emp { addEmployee() };
  shiftSupervisor visor { emp };

  visor.setAnnualSalary(query<unsigned>("Input Employee Annual Salary: "));
  visor.setBonus(query<unsigned>("Input Employee Annual Bonus: "));

  return visor;
}

teamLeader addTeamLeader(void)
{
  teamLeader tl { addProdWorker() };

  tl.setMonthlyBonus(
    query<unsigned>("Input Employee Monthly Bonus: "));

  tl.setReqTrainingHours(
    query<unsigned>("Input Employee Required Training Hours: "));

  tl.setTrainingHours(
    query<unsigned>("Input Employee Completed Training Hours: "));

  return tl;
}

/// prints 30 lines of whitespace to mimic the screen being wiped. Tried to get
/// ANSI sequences on windows last semester and it didn't work.
void sscroll(void) 
{
  for (int i {}; i < 10; ++i) cout << '\n';
  cout.flush();
}
