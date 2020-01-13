#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
public:
  float Utilization();  // DONE: See src/processor.cpp

  // create setters for future expansion with restrictions. otherwise could
  // have made them public
  void user(long user) { user_ = user; }
  void nice(long nice) { nice_ = nice; }
  void system(long system) { system_ = system; }
  void idle(long idle) { idle_ = idle; }
  void iowait(long iowait) { iowait_ = iowait; }
  void irq(long irq) { irq_ = irq; }
  void softirq(long softirq) { softirq_ = softirq; }
  void steal(long steal) { steal_ = steal; }
  void guest(long guest) { guest_ = guest; }
  void guest_nice(long guest_nice) { guest_nice_ = guest_nice; }
  // TODO: should provide getters if setters are provided

  // DONE: Declare any necessary private members
private:
  // time is in USER_HZ (typically hundreths of a second) so use long since values can be large
  long user_;
  long nice_;
  long system_;
  long idle_;
  long iowait_;
  long irq_;
  long softirq_;
  long steal_;
  long guest_;
  long guest_nice_;
};

#endif
