#ifndef Timer_hpp
#define Timer_hpp

#include "main.h"

class Timer{
private:
  std::uint32_t endTime;
public:
  void setTimerMS(std::uint32_t ms){
    endTime = pros::millis()+ms;
  }

  bool isExpired(){
    return(pros::millis() > endTime);
  }
};

#endif
