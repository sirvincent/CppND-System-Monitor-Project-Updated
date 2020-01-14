#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid()
{
  return pid_;
}

void Process::Pid(int pid)
{
  pid_ = pid;
}

// DONE: Return the user (name) that generated this process
string Process::User()
{
  return user_;
}

void Process::User(std::string user)
{
  user_ = user;
}

// DONE: Return the command that generated this process
string Process::Command()
{
  return command_;
}

void Process::Command(std::string command)
{
  command_ = command;
}

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}
