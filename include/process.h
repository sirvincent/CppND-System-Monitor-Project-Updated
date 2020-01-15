#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
  int Pid();                               // DONE: See src/process.cpp
  void Pid(int pid);
  std::string User();                      // DONE: See src/process.cpp
  void User(std::string user);
  std::string Command();                   // DONE: See src/process.cpp
  void Command(std::string command);
  std::string Ram();                       // DONE: See src/process.cpp
  void Ram(std::string ram);
  float CpuUtilization();                  // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
private:
  int pid_;
  std::string user_;
  std::string command_;
  std::string ram_;
};

#endif
