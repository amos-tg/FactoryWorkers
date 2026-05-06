#include "factory.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

/// submenu path for option 1 in the main menu
void newEmployee(void);

/// returns an employee, queries user for all fields in an employee class.
employee addEmployee(void);

/// returns a productionWorker, queries for all owned values that
/// make up the returned value.
productionWorker addProdWorker(void);

/// returns a shiftSupervisor, queries for all owned values that
/// make up the returned value.
shiftSupervisor addShiftSupervisor(void);

/// returns a teamLeader, queries for all owned values that
/// make up the returned value.
teamLeader addTeamLeader(void);

/// prints 30 lines of whitespace to scroll down the screen. 
void sscroll(void);

const string main_menu = 
R"(Factory Employee Manager:
  1) New Employee
  
  2) Exit

  (input 1 or 2) : )";

// exit is defined in multiple menus so namespacing from enum class is needed
enum class menuOpt { NEW = 1, EXIT };

int main(void) 
{
  while (true) 
  {
    unsigned opt;

    sscroll();
    cout << main_menu;
    cout.flush();
    cin >> opt;

    /// if user doesn't input something valid, reset the stream and query again
    if (!cin) 
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    switch (static_cast<menuOpt>(opt))
    {
    case menuOpt::NEW:
      newEmployee();
      break;

    case menuOpt::EXIT:
      exit(EXIT_SUCCESS);

    // if the value parses as an unsigned but isn't valid start over 
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
  PRODUCTION_WORKER = 1, SHIFT_SUPERVISOR,
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
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    // Add* fns return their objects so that the inheriting types can take
    // advantage of their base's function.
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

/// Typename T: the type inserted into by cin
/// msg: the message outputted to stdout
///
/// Queries the user for a value of type T with the message msg.
template<typename T>
T query(const char* msg)
{
  T opt;
  while (true)
  {
    cout << msg;
    cout.flush();

    cin >> opt;

    // if cin failed to input into opt or still has chars in the internal buffer
    if (cin.fail() || cin.peek() != '\n')
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

  // checks for exceptions and continuosly queries until a valid value is
  // recieved
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

  // checks for exceptions and continuosly queries until a valid value is
  // recieved
  while (true)
  {
    string name {};

    cout << "Input Employee Name: "; 
    cout.flush();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    emp.setName(name);

    if (cin.good()) break;
  }

  // checks for exceptions and continuosly queries until a valid value is
  // recieved
  while (true)
  {
    chrono::day day { 
      query<unsigned>("Input Employee Hiring Date Day Number: ") };

    chrono::year year { 
      query<int>("Input Employee Hiring Date Year Number: ") };
    
    chrono::month month { 
      query<unsigned>("Input Employee Hiring Date Month Number: ") };

    chrono::year_month_day ymd { year, month, day };

    if (ymd.ok())
    {
      emp.setDateHired(ymd);
      break;
    } 
    else cerr << "Error: Invalid Date" << endl;
  }

  return emp;
}

productionWorker addProdWorker(void)
{
  employee emp { addEmployee() };
  productionWorker pr_wkr { emp };

  // checks for exceptions and continuosly queries until a valid value is
  // recieved
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

  // checks for exceptions and continuosly queries until a valid value is
  // recieved
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

void sscroll(void) 
{
  for (int i {}; i < 10; ++i) cout << '\n';
  cout.flush();
}
