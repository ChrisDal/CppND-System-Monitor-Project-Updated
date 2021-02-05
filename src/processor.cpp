#include <vector>
#include <string>

#include "processor.h"
#include "linux_parser.h"

// Processor Constructor
Processor::Processor() {
  // Define the times 
  std::vector<std::string> cpuse = LinuxParser::CpuUtilization(); 
  // Value at instant T since the launch 
  IdleTime(cpuse); 
  RunningTime(cpuse); 
  SetTotalTime(); 
  // new reference for delta cpu usage 
  d_idle_time_ = idle_time_; 
  d_running_time_ = running_time_;
  d_total_time_ = total_time_;
  // init time 
  init_time = true; 
}

// Return the aggregate CPU utilization
float Processor::Utilization() { 
  std::vector<std::string> cpuse = LinuxParser::CpuUtilization(); 
  float cpu_used = 0.0;
  IdleTime(cpuse); 
  RunningTime(cpuse); 
  SetTotalTime(); 
  cpu_used =  RunningTime() / float(TotalTime());
  return cpu_used; 
}

// Return the CPU utilization since monitor launch
float Processor::Instant_Utilization() { 
  std::vector<std::string> cpuse = LinuxParser::CpuUtilization();
  IdleTime(cpuse); 
  RunningTime(cpuse); 
  SetTotalTime();  
  // Define "instant cpu" usage after initialization
  if (init_time) {
    // At init time take the cpu classic usage 
    init_time = false; 
    return Processor::Utilization(); 
  } 
  return (RunningTime() - d_running_time_) / float(TotalTime() - d_total_time_);
}


// Private member handling 
void Processor::IdleTime(std::vector<std::string> cpuse)  {
   // idle + iowait 
  idle_time_ = std::stoull(cpuse[3]) + std::stoull(cpuse[4]);
}

void Processor::RunningTime(std::vector<std::string> cpuse)  {
  // NonIdle =  Running  = user + nice + system + irq + softirq + steal
  // where usertime = use + guest 
  // and nice = nice - guest_nice 
  running_time_ = std::stoull(cpuse[0]) + std::stoull(cpuse[1]) + std::stoull(cpuse[2]) + std::stoull(cpuse[5]) + std::stoull(cpuse[6]) + std::stoull(cpuse[7]);
}

void Processor::SetTotalTime()  {
  total_time_ = IdleTime() + RunningTime();
}


unsigned long long int Processor::IdleTime() const {
  return idle_time_;
}

unsigned long long int Processor::RunningTime() const {
  return running_time_;
}

unsigned long long int Processor::TotalTime() const {
  return total_time_;
}