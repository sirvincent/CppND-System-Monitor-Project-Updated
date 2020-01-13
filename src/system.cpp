#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu()
{
  std::vector<string> cpuUtilizationString = LinuxParser::CpuUtilization();

  // whos job is it to convert to long, this function or Process? I think this function
  cpu_.user(std::stol(cpuUtilizationString[0]));
  cpu_.nice(std::stol(cpuUtilizationString[1]));
  cpu_.system(std::stol(cpuUtilizationString[2]));
  cpu_.idle(std::stol(cpuUtilizationString[3]));
  cpu_.iowait(std::stol(cpuUtilizationString[4]));
  cpu_.irq(std::stol(cpuUtilizationString[5]));
  cpu_.softirq(std::stol(cpuUtilizationString[6]));
  cpu_.steal(std::stol(cpuUtilizationString[7]));
  cpu_.guest(std::stol(cpuUtilizationString[8]));
  cpu_.guest_nice(std::stol(cpuUtilizationString[9]));

  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
  return processes_;
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization()
{
  return LinuxParser::MemoryUtilization();
}

// DONE: Return the number of seconds since the system started running
long int System::UpTime()
{
  return LinuxParser::UpTime();
}

// DONE: Return the total number of processes on the system
int System::TotalProcesses()
{
  return LinuxParser::TotalProcesses();
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses()
{
  return LinuxParser::RunningProcesses();
}


// DONE: Return the system's kernel identifier (string)
std::string System::Kernel()
{
  return LinuxParser::Kernel();
}

// DONE: Return the operating system name
std::string System::OperatingSystem()
{
  return LinuxParser::OperatingSystem();
}

