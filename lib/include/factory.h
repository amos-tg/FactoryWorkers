#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <chrono>
#include <exception>

// factory worker classes, all of the types of employees at a factory.

class employee
{
  std::string name_m;
  std::chrono::year_month_day date_hired_m;
  unsigned id_m;
public:
  /// id: the employee's identification number
  /// name: the employee's name
  /// date_hired: the date on which the employee was hired
  ///
  /// constructs an employee object. Throws an invalidEmployeeNumber
  /// exception if the id argument passed isn't within the inclusive range 0 to
  /// 9999. 
  employee(
      unsigned id, std::string name, std::chrono::year_month_day date_hired);

  /// returns the employee's identification number
  inline unsigned getId(void) const
  { return id_m; }

  /// returns the employee's name
  inline std::string getName(void) const
  { return name_m; }

  /// returns the employee's hiring date
  inline std::chrono::year_month_day getDateHired(void) const
  { return date_hired_m; };

  /// Sets the employee's identification number. Throws an invalidEmployeeNumber
  /// exception if the id argument passed isn't within the inclusive range 0 to
  /// 9999.
  void setId(unsigned id);

  /// sets the employee's name
  inline void setName(std::string name)
  { name_m = name; }

  /// sets the hiring date of the employee
  inline void setDateHired(std::chrono::year_month_day ymd)
  { date_hired_m = ymd; }

  /// prints all employee information
  void printEmployee(void) const;
private:
  /// returns true if the passed id is between 0 && 9999, else returns false.
  static bool isIdValid(unsigned id);
};

class invalidEmployeeNumber: public std::exception
{
  unsigned id_m;
  std::string msg;
public:
  invalidEmployeeNumber(unsigned emp_id);

  const char* what() const noexcept override 
  { return msg.c_str(); };

  inline unsigned getId(void) const
  { return id_m; }
};

class productionWorker: public employee
{
public:
  /// represents the shift the worker covers
  enum shift { DAY = 1, NIGHT };

  /// shift: the DAY or NIGHT shift the worker covers
  /// hourly_pay: the amount the worker is payed per hour
  /// emp: the employee becoming a productionWorker
  ///
  /// constructs a productionWorker. Throws invalidShift if the shift passed 
  /// is not DAY=1 or NIGHT=2 from productionWorker::shift. Throws 
  /// invalidPayRate if the hourly_pay passed is negative.
  productionWorker(shift shift, unsigned hourly_pay, employee emp);

  /// returns the shift of the productionWorker
  inline shift getShift(void) const 
  { return shift_m; }

  /// returns the productionWorkers hourly pay
  inline unsigned getHourlyPay(void) const
  { return hourly_pay_m; }

  /// sets the shift the productionWorker covers, throws invalidShift if the
  /// shift passed is not DAY=1 or NIGHT=2 from productionWorker::shift.
  void setShift(shift shift);

  /// sets the hourly pay of the productionWorker, throws invalidPayRate if the
  /// hourly_pay passed is negative.
  void setHourlyPay(unsigned hourly_pay);

  /// prints all the productionWorkers data, including the employee data 
  void printProductionWorker(void) const;
private:
  // shift not declared before 1st pub section. so vars are down here
  shift shift_m;
  unsigned hourly_pay_m;

  /// returns true if shift is DAY=1, or NIGHT=2, else false is returned.
  static bool isShiftValid(productionWorker::shift shift);

  /// returns true if hr_pay isn't negative, else false is returned. 
  static bool isHourlyPayValid(unsigned hr_pay);
};

class invalidShift: public std::exception {
  productionWorker::shift shift_m;
  std::string msg;
public:
  invalidShift(productionWorker::shift shift);

  inline const char* what() const noexcept override
  { return msg.c_str(); }

  inline productionWorker::shift getShift(void) const
  { return shift_m; }
}; 

class invalidPayRate: public std::exception {
  unsigned hourly_pay_m;
  std::string msg;
public:
  invalidPayRate(unsigned hrly_pay);

  inline const char* what() const noexcept override
  { return msg.c_str(); }
  
  inline unsigned getHourlyPay(void) const 
  { return hourly_pay_m; }
};

class shiftSupervisor: public employee
{
  unsigned annual_salary_m;
  unsigned bonus_m; // payed annually
public:
  /// annual_salary: the shiftSupervisor's annual salary
  /// annual_bonus: the bonus payed yearly
  /// emp: the employee that is becoming a shiftSupervisor
  ///
  /// constructs a shiftSupervisor object
  shiftSupervisor(unsigned annual_salary, unsigned annual_bonus, employee emp);

  /// returns the annual salary
  inline unsigned getAnnualSalary(void) const
  { return annual_salary_m; }

  /// returns the annual bonus 
  inline unsigned getBonus(void) const
  { return bonus_m; }

  /// sets the annual salary
  inline void setAnnualSalary(unsigned annual_salary)
  { annual_salary_m = annual_salary; }

  /// sets the annual bonus
  inline void setBonus(unsigned bonus)
  { bonus_m = bonus; }

  /// prints all the data of the shiftSupervisor, including employee data. 
  void printShiftSupervisor() const;
};

class teamLeader: public productionWorker
{
  unsigned monthly_bonus_m;
  unsigned req_train_hours_m;
  unsigned train_hours_m;
public:
  /// monthly_bonus: the teamLeaders monthly pay bonus
  /// req_train_hr: the teamLeaders required training hours
  /// train_hours: the teamLeaders completed training hours
  /// prod_worker: the productionWorker becoming a teamLeader
  ///
  /// constructs a teamLeader object
  teamLeader(
    unsigned monthly_bonus, unsigned req_train_hr, 
    unsigned train_hours, productionWorker prod_worker);

  /// returns the monthly pay bonus
  inline unsigned getMonthlyBonus(void) const
  { return monthly_bonus_m; }

  /// returns the required training hours
  inline unsigned getReqTrainingHours(void) const
  { return req_train_hours_m; }

  /// returns the completed training hours
  inline unsigned getTrainHours(void) const
  { return train_hours_m; }

  /// sets the monthly pay bonus
  inline void setMonthlyBonus(unsigned bonus)
  { monthly_bonus_m = bonus; }

  /// sets the required training hours
  inline void setReqTrainingHours(unsigned hours)
  { req_train_hours_m = hours; }

  /// sets the mandatory training hours
  inline void setTrainingHours(unsigned hours)
  { train_hours_m = hours; }

  /// prints all of the teamLeader's data, including the productionWorker and
  /// employee derived data members.
  void printTeamLeader(void) const;
};

#endif
