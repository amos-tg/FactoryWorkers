#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <chrono>

class employee
{
  std::string name_m;
  std::chrono::year_month_day date_hired_m;
  unsigned id_m;
public:
  employee(
      unsigned id, std::string name, std::chrono::year_month_day date_hired);

  inline unsigned getId(void) const
  { return id_m; }

  inline std::string getName(void) const
  { return name_m; }

  inline std::chrono::year_month_day getDateHired(void) const
  { return date_hired_m; };

  inline void setId(unsigned id)
  { id_m = id; }

  inline void setName(std::string name)
  { name_m = name; }

  inline void setDateHired(std::chrono::year_month_day ymd)
  { date_hired_m = ymd; }

  /// prints all employee information
  void printEmployee(void) const;
};


class productionWorker: public employee
{
public:
  // directions say day = 1, night = 2
  enum shift { DAY = 1, NIGHT };

  productionWorker(shift shift, unsigned hourly_pay, employee emp);

  inline shift getShift(void) const 
  { return shift_m; }

  inline unsigned getHourlyPay(void) const
  { return hourly_pay_m; }

  inline void setShift(shift shift)
  { shift_m = shift; }

  inline void setHourlyPay(unsigned hourly_pay)
  { hourly_pay_m = hourly_pay; }

  void printProductionWorker(void) const;
private:
  shift shift_m;
  unsigned hourly_pay_m;
};

class shiftSupervisor: public employee
{
  unsigned annual_salary_m;
  unsigned bonus_m;
public:
  shiftSupervisor(unsigned annual_salary, unsigned bonus, employee emp);

  inline unsigned getAnnualSalary(void) const
  { return annual_salary_m; }

  inline unsigned getBonus(void) const
  { return bonus_m; }

  inline void setAnnualSalary(unsigned annual_salary)
  { annual_salary_m = annual_salary; }

  inline void setBonus(unsigned bonus)
  { bonus_m = bonus; }

  void printShiftSupervisor() const;
};

class teamLeader: public productionWorker
{
  unsigned monthly_bonus_m;
  unsigned req_train_hours_m;
  unsigned train_hours_m;
public:
  teamLeader(
    unsigned monthly_bonus, unsigned req_train_hr, 
    unsigned train_hours, productionWorker prod_worker);

  inline unsigned getMonthlyBonus(void) const
  { return monthly_bonus_m; }

  inline unsigned getReqTrainingHours(void) const
  { return req_train_hours_m; }

  inline unsigned getTrainHours(void) const
  { return train_hours_m; }

  inline void setMonthlyBonus(unsigned bonus)
  { monthly_bonus_m = bonus; }

  inline void setReqTrainingHours(unsigned hours)
  { req_train_hours_m = hours; }

  inline void setTrainingHours(unsigned hours)
  { train_hours_m = hours; }

  void printTeamLeader(void) const;
};

#endif
