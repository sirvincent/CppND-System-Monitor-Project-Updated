#include "format.h"

#include <algorithm>
#include <cassert>
#include <string>

using std::string;

void Format::formatNumber(string &number) {
  if (number.size() == 1) {
    number = string("0") + number;
  }
}

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  // display can only show up to 99 hours
  if (seconds > 360000) {
    seconds = seconds % 360000;
  }

  long hours = seconds / 3600;
  if (hours > 0) {
    seconds = seconds % 3600;
  }
  long minutes = seconds / 60;
  if (minutes > 0) {
    seconds = seconds % 60;
  }

  // TODO: this is messy how to make this nicer? std::format (C++20), sprintf?
  string hourString = std::to_string(hours);
  formatNumber(hourString);
  string minutesString = std::to_string(minutes);
  formatNumber(minutesString);
  string secondsString = std::to_string(seconds);
  formatNumber(secondsString);
  // similar things should be in tests
  assert(hourString.size() == 2);
  assert(minutesString.size() == 2);
  assert(secondsString.size() == 2);

  string elapsedTime = hourString + ":" + minutesString + ":" + secondsString;

  return elapsedTime;
}
