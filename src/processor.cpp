#include "processor.h"

// DONE: Return the aggregate CPU utilization
// TODO: (BONUS) very stable calculation since it is per boot calculate in a user defined time window the utilization
float Processor::Utilization()
{
  long idleTime = idle_ + iowait_;
  long notIdleTime = user_ + nice_ + system_ + irq_ + softirq_ + steal_;

  long totalTime = idleTime + notIdleTime;

  float cpuUsage = static_cast<float>(notIdleTime) / totalTime;

  return cpuUsage;
}

/*
Utilization calculation:
https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald
*/
