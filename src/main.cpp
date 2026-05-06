#include "factory.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void newEmployee(void);

void addProdWorker(void);

void addShiftSupervisor(void);

void addTeamLeader(void);

void sscroll(void);

const char QUIT { 'q' };

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
      cin.ignore();
      cin.clear();
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
      cin.ignore();
      cin.clear();
      continue;
    }

    switch (static_cast<employeeType>(opt))
    {
    case employeeType::PRODUCTION_WORKER:
      addProdWorker();
      return;

    case employeeType::SHIFT_SUPERVISOR:
      addShiftSupervisor();
      return;

    case employeeType::TEAM_LEADER:
      addTeamLeader();
      return;

    case employeeType::EXIT:
      exit(EXIT_SUCCESS);

    default:
      continue;
    }
  }
}

/// prints 30 lines of whitespace to mimic the screen being wiped. Tried to get
/// ANSI sequences on windows last semester and it didn't work.
void sscroll(void) 
{
  for (int i {}; i < 10; ++i) cout << '\n';
  cout.flush();
}
