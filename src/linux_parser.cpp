#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <cassert>
#include <filesystem>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string memoryTotalString, memoryFreeString, unitTotal, unitFree;
  string line, name, value, unit;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> name >> value >> unit;
      if (name == "MemTotal") {
        memoryTotalString = value;
        unitTotal = unit;
      } else if (name == "MemFree") {
        memoryFreeString = value;
        unitFree = unit;
      }
    }
    // otherwise the calculation is wrong
    assert(unitTotal == unitFree);
  }

  float memoryTotal = std::stof(memoryTotalString);
  float memoryFree = std::stof(memoryFreeString);
  float memoryUtilization = (memoryTotal - memoryFree) / memoryTotal;
  return memoryUtilization;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime, suspendTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime >> suspendTime;
    }
  }

  return std::stol(uptime);
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string totalProcesses;
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "processes") {
        totalProcesses = value;
      }
    }
  }

  return std::stoi(totalProcesses);
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  // TODO: repeat of TotalProcesses, inefficient and duplication of opening
  // /proc/stat, refactor
  //       into stat object?
  string runningProcesses;
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "procs_running") {
        runningProcesses = value;
      }
    }
  }

  return std::stoi(runningProcesses);
}

// DONE: Read and return CPU utilization
// TODO: BONUS: read in each separate core usage in place of total
vector<string> LinuxParser::CpuUtilization() {
  string key, value;
  string line;
  std::vector<string> values{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        for (int idx{0}; idx < 10; idx++) {
          linestream >> value;
          values.push_back(value);
        }
      }
    }
  }
  return values;
}

// DONE: BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  std::filesystem::path directory(kProcDirectory);
  assert(directory.is_absolute());

  for (std::filesystem::directory_entry const &dir :
       std::filesystem::directory_iterator(directory)) {
    if (dir.is_directory()) {
      std::string path_string = dir.path().filename().string();
      if (std::all_of(path_string.begin(), path_string.end(), isdigit)) {
        int pid = std::stoi(path_string);
        pids.push_back(pid);
      }
    }
  }
  return pids;
}

// DONE: Read and return the user ID associated with a process
// DONE: REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string key, value;
  string line;
  string uid;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "Uid") {
        uid = value;
      }
    }
  }

  return uid;
}

// DONE: Read and return the user associated with a process
// DONE: REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) {
  string loginName, password, userID, groupID, comment, home, optional;
  string line;

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      // note there are possible 7 fields, 2 are optional
      // there are optional parameters which are sometimes empty and hence ::
      // exists
      std::string::size_type position = line.find("::");
      while (position != std::string::npos) {
        // TODO: check if at the right position is inserted might need a +1
        line.insert(position + 1, "x");
        position = line.find("::");
      }
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream linestream(line);
      linestream >> loginName >> password >> userID >> groupID >> comment >>
          home >> optional;
      // a process should only have one login name, ensured by /etc/passwd I
      // hope
      if (std::stoi(userID) == uid) {
        return loginName;
      }
    }
  }
  return loginName;
}

// DONE: Read and return the command associated with a process
// DONE: REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    // TODO: assert if only a single line
    std::getline(stream, command);
  }

  return command;
}

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string ram;
  string line, key, value, unit;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value >> unit;

      if (key == "VmSize:") {
        ram = value;
        // check since we will convert in Ram, although this is the
        // responsibility of Process
        assert(unit == "kB");
      }
    }
  }

  return ram;
}

std::vector<string> LinuxParser::StatReader(int pid) {
  std::vector<string> fields;
  string line, field;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    // Assert that it is only a single line?
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> field) {
      fields.push_back(field);
    }
  }

  return fields;
}

// DONE: Read and return the uptime of a process
// DONE: REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::vector<string> fields = StatReader(pid);

  long uptime = std::stol(fields[21]) / sysconf(_SC_CLK_TCK);

  return uptime;
}

float LinuxParser::CpuUtilization(int pid) {
  long uptime = UpTime();

  std::vector<string> fields = StatReader(pid);

  long utime = std::stol(fields[13]);
  long stime = std::stol(fields[14]);
  long cutime = std::stol(fields[15]);
  long cstime = std::stol(fields[16]);
  long starttime = std::stol(fields[21]);

  long total_time = utime + stime;
  total_time = total_time + cutime + cstime;
  float seconds = uptime - (starttime / sysconf((_SC_CLK_TCK)));
  float cpu_utilization = (total_time / sysconf(_SC_CLK_TCK)) / seconds;

  return cpu_utilization;
}
