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

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
  vector<int> pids = LinuxParser::Pids();

  // clear to circumvent double entries, is it better to look only for 'dead' and new ones?
  //   it will be complexer, at maybe a marginel efficiency boost?
  processes_.clear();
  for (auto pid : pids)
  {
    Process process;
    process.Pid(pid);

  // add new pids to vector
    int const &pid = process.Pid();
    string uid  = LinuxParser::Uid(pid);
    // I find it interesting that I need to check again if string is not empty, I though stream.is_open() will ensure file exists
    // but maybe not all processes have a Uid string? Or it process stops stream.is_open() check?
    if (uid.empty())
    {
      continue;
    }
    string user = LinuxParser::User(std::stoi(uid));
    process.User(user);

    // TODO: at a certain point in time the command from one overlaps with the order, how?
    string command = LinuxParser::Command(pid);
    process.Command(command);

    string ram = LinuxParser::Ram(pid);
    if (ram.empty())
    {
      continue;
    }
    // ram is always in kB (due to the assert) but we want show in MB
    // I think this is a job of system to convert? since it manages Process and communicates to the display
    long ramInteger = std::stoi(ram) / 1000;
    process.Ram(std::to_string(ramInteger));

    long uptime = LinuxParser::UpTime(pid);
    process.UpTime(uptime);

    float cpu_utilization = LinuxParser::CpuUtilization(pid);
    process.CpuUtilization(cpu_utilization);

    processes_.push_back(process);
  }

  // TODO: better to immediately sort larger then requires passing a function std::sort,
  //       but we are required to overload operator< so do it in this way
  std::sort(processes_.begin(), processes_.end());
  std::reverse(processes_.begin(), processes_.end());

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

