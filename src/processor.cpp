#include "processor.h"

// DONE: Return the aggregate CPU utilization
// TODO: (BONUS) very stable calculation since it is per boot calculate in a
// user defined time window the utilization
float Processor::Utilization() {
  long idleTime = idle_ + iowait_;
  long notIdleTime = user_ + nice_ + system_ + irq_ + softirq_ + steal_;

  long totalTime = idleTime + notIdleTime;

  float cpuUsage = static_cast<float>(notIdleTime) / totalTime;

  return cpuUsage;
}
