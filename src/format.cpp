#include "format.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <iomanip>


// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long secondsTotal) {

  // display can only show up to 99 hours
  if (secondsTotal > 360000) {
    secondsTotal = secondsTotal % 360000;
  }

  long hours = secondsTotal / 3600;
  long minutes = (secondsTotal % 3600) / 60;
  long seconds = (secondsTotal % 3600 % 60);

  //setw and setfill for adding leading zeros
  std::ostringstream hourStream, minuteStream, secondStream;
  hourStream << std::setw(2) << std::setfill('0') << hours;
  minuteStream << std::setw(2) << std::setfill('0') << minutes;
  secondStream << std::setw(2) << std::setfill('0') << seconds;

  std::string elapsedTime = hourStream.str() + ":" + minuteStream.str() + ":" + secondStream.str();
  return elapsedTime;
}
