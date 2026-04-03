#include <string>
#include <chrono>

class employee
{
  unsigned id_m;
  std::string name_m;
  std::chrono::time_point<std::chrono::system_clock> date_hired_m;
public:
  employee();

  inline unsigned getId(void)
  { return id_m; }

  inline std::string getName(void)
  { return name_m; }

  inline std::chrono::time_point<std::chrono::system_clock> getDateHired(void)
  { return date_hired_m; };

  /// prints all employee information
  void printEmployee(void);
};

// directions say day = 1, night = 2
enum shift { DAY = 1, NIGHT };

class productionWorker: public employee
{
  shift shift_m;
  unsigned hourly_pay_m;
public:
  productionWorker(shift shift, unsigned hourly_pay);

  inline shift getShift(void)
  { return shift_m; }

  inline unsigned getHourlyPay(void)
  { return hourly_pay_m; }

  void printProductionWorker(void);
};

class shiftSupervisor;

class teamLeader;
