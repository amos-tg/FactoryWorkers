#include "factory.h"
#include <iostream>

using namespace std;

void newEmployee(void);

void printEmployee(void);

void sscroll(void);

const char QUIT { 'q' };

const string main_menu = 
R"(Factory Employee Manager:
  1) New Employee
  2) Print Worker Data

  3) Exit
  
  (input 1-3) : )";

// exit is defined in multiple menus so namespacing from enum class is needed
enum class menuOpt { NEW = 1, PRINT, EXIT, };

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
      cin.ignore();
      cin.clear();
      continue;
    }

    switch (static_cast<menuOpt>(opt))
    {
    case menuOpt::NEW:
      newEmployee();
      break;

    case menuOpt::PRINT:
      printEmployee();
      break;

    default:
      continue;        
    }
  }
}

const char* emp_type_menu =
R"(Pick Employee Type to be Added:
  1) Employee
  2) Production Worker
  3) Shift Supervisor
  4) Team Leader

  ) Exit

  (input 1-4 or q): )";

enum class employeeType 
{ 
  EMPLOYEE = 1, PRODUCTION_WORKER,
  SHIFT_SUPERVISOR, TEAM_LEADER, EXIT
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
      cin.ignore();
      cin.clear();
      continue;
    }

    switch (static_cast<employeeType>(opt))
    {
    case employeeType::EMPLOYEE:

      break;
    }
  }
}

void printEmployee(void)
{

}

/// prints 30 lines of whitespace to mimic the screen being wiped. Tried to get
/// ANSI sequences on windows last semester and it didn't work.
void sscroll(void) 
{
  for (int i {}; i < 10; ++i) cout << '\n';
  cout.flush();
}
