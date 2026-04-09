#include "factory.h"
#include <iostream>
#include <cassert>

using namespace std;

const char 
  *TEST_PASSED { "Passed" },  
  *EMPLOYEE_TESTS { "Test (employee class): " },
  *PRODUCTION_WORKER_TESTS { "Test (productionWorker class): " },
  *SHIFT_SUPERVISOR_TESTS { "Test (shiftSupervisor class): " },
  *TEAM_LEADER_TESTS { "Test (teamLeader class): " },
  *CONSTRUCTOR_CHAINING_TESTS { "Test (Constructor Chaining): " };

void employee_tests(void);
void production_worker_tests(void);
void shift_supervisor_tests(void);
void team_leader_tests(void);
void constructor_chaining_tests(void);

int main(void) 
{
  void employee_tests();
  cout << '\n';
  void production_worker_tests();
  cout << '\n';
  void shift_supervisor_tests();
  cout << '\n';
  void team_leader_tests();
  cout << '\n';
  void constructor_chaining_tests();
  cout << endl;

  return 0;
}


void employee_tests()
{
  unsigned id { 499 }; 
  string name { "Jarmenius Shartruese" };
  chrono::year_month_day date_hired { 
      chrono::year { 1999 }, chrono::month { 20 }, chrono::day { 1 } };
  employee emp { id, name, date_hired }; 
  assert(emp.getId() == id);
  assert(emp.getName() == name);
  assert(emp.getDateHired() == date_hired);

  id = 600; 
  name = "Bardoushtae Chourdle";
  date_hired = chrono::year_month_day { 
    chrono::year { 2000 }, chrono::month { 10 }, chrono::day { 3 } };
  emp.setId(id);
  emp.setName(name);
  emp.setDateHired(date_hired);  
  assert(emp.getId() == id);
  assert(emp.getName() == name);
  assert(emp.getDateHired() == date_hired);

  emp.printEmployee();
}
