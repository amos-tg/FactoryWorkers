#include "factory.h"
#include <iostream>
#include <cassert>

using namespace std;

const char 
  *TEST_PASSED { "Passed" },  
  *EMPLOYEE_TESTS { "Test (employee class): " },
  *PRODUCTION_WORKER_TESTS { "Test (productionWorker class): " },
  *SHIFT_SUPERVISOR_TESTS { "Test (shiftSupervisor class): " },
  *TEAM_LEADER_TESTS { "Test (teamLeader class): " };

/// class respective tests (factory.h encompassing)
void employee_tests(void);
void production_worker_tests(void);
void shift_supervisor_tests(void);
void team_leader_tests(void);

int main(void) 
{
  employee_tests();
  cout << '\n';
  production_worker_tests();
  cout << '\n';
  shift_supervisor_tests();
  cout << '\n';
  team_leader_tests();
  cout << endl;

  return 0;
}

void employee_tests(void)
{
  cout << EMPLOYEE_TESTS << "\nEmployee 1:\n";

  unsigned id { 499 }; 
  string name { "Jarmenius Shartruese" };
  chrono::year_month_day date_hired { 
      chrono::year { 1999 }, chrono::month { 11 }, chrono::day { 1 } };

  employee emp { id, name, date_hired }; 

  /// tests constructor behavior
  assert(emp.getId() == id);
  assert(emp.getName() == name);
  assert(emp.getDateHired() == date_hired);

  /// visually validated output of printEmployee
  emp.printEmployee();

  cout << "\nEmployee 2 \n";

  id = 600; 
  name = "Bardoushtae Chourdle";
  date_hired = chrono::year_month_day { 
    chrono::year { 2000 }, chrono::month { 10 }, chrono::day { 3 } };

  emp.setId(id);
  emp.setName(name);
  emp.setDateHired(date_hired);  

  /// validates the setters
  assert(emp.getId() == id);
  assert(emp.getName() == name);
  assert(emp.getDateHired() == date_hired);

  /// visually validated output of printEmployee
  emp.printEmployee();
  
  cout << TEST_PASSED << endl;
}

void production_worker_tests(void)
{
  cout << PRODUCTION_WORKER_TESTS; 

  // create the base emp for the prod workers to use
  unsigned id { 499 }; 
  string name { "Jarmeenius Shartruese" };
  chrono::year_month_day date_hired { 
      chrono::year { 1999 }, chrono::month { 11 }, chrono::day { 1 } };

  employee emp { id, name, date_hired }; 

  // create two production workers
  productionWorker 
    work1 { productionWorker::NIGHT, 15, emp }, 
    work2 { productionWorker::DAY, 25, emp };

  // validate the prod workers visually 
  cout << "\nProduction Worker 1:\n";
  work1.printProductionWorker();

  cout << "\nProduction Worker 2:\n";
  work2.printProductionWorker();

  cout << TEST_PASSED << endl;
}

void shift_supervisor_tests(void)
{
  cout << SHIFT_SUPERVISOR_TESTS << '\n';

  // create the base emp for the shift supervisor to use
  unsigned id { 499 }; 
  string name { "Jarmeenius Shartruese" };
  chrono::year_month_day date_hired { 
      chrono::year { 1999 }, chrono::month { 11 }, chrono::day { 1 } };

  employee emp { id, name, date_hired }; 

  shiftSupervisor boss { 78'000, 2000, emp };

  // verify hierarchy's data prints correctly.
  boss.printShiftSupervisor();

  cout << TEST_PASSED << endl;
}

void team_leader_tests(void)
{
  cout << TEAM_LEADER_TESTS << '\n';
   
  // create the base emp for the teamLeader to use
  unsigned id { 499 }; 
  string name { "Jarmeenius Shartruese" };
  chrono::year_month_day date_hired { 
      chrono::year { 1999 }, chrono::month { 11 }, chrono::day { 1 } };

  // thought this would be preferable, seems similarly ug to big arg list
  teamLeader boss { 500, 30, 29, 
    productionWorker { productionWorker::NIGHT, 25, 
      employee { id, name, date_hired } } }; 


  // verify all the data prints correctly
  boss.printTeamLeader();

  cout << TEST_PASSED << endl;
}
