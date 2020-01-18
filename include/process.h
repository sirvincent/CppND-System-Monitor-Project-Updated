#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;  // DONE: See src/process.cpp
  void Pid(int pid);
  std::string User() const;  // DONE: See src/process.cpp
  void User(std::string user);
  std::string Command() const;  // DONE: See src/process.cpp
  void Command(std::string command);
  std::string Ram() const;  // DONE: See src/process.cpp
  void Ram(std::string ram);
  long int UpTime() const;  // DONE: See src/process.cpp
  void UpTime(long int uptime);
  float CpuUtilization() const;  // DONE: See src/process.cpp
  void CpuUtilization(float cpu_utilization);
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp

  // DONE: Declare any necessary private members
 private:
  int pid_;
  std::string user_;
  std::string command_;
  std::string ram_;
  long int uptime_;
  float cpu_utilization_;
};

#endif
