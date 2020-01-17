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

// DONE: Return this process's memory utilization
string Process::Ram()
{
  return ram_;
}

void Process::Ram(std::string ram)
{
  ram_ = ram;
}

// DONE: Return the age of this process (in seconds)
long int Process::UpTime()
{
  return uptime_;
}

void Process::UpTime(long int uptime)
{
  uptime_ = uptime;
}

// DONE: Return this process's CPU utilization
float Process::CpuUtilization()
{
  return cpu_utilization_;
}

void Process::CpuUtilization(float cpu_utilization)
{
  cpu_utilization_ = cpu_utilization;
}

// DONE: Overload the "less than" comparison operator for Process objects
// DONE: REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &other) const
{
  return cpu_utilization_ < other.cpu_utilization_;
}
