#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// constructor 
System::System() {
  SetKernel(); 
  SetOps();
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int> linux_pids = LinuxParser::Pids();
  for (const auto& p : linux_pids) 
    processes_.push_back(Process(p));
  return processes_; 
}

// Return the system's kernel identifier (string)
std::string System::Kernel() const {
  return kernel_;
}

void System::SetKernel() {
  kernel_ = LinuxParser::Kernel(); 
}

// Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() const { 
  return ops_; 
}

void System::SetOps() {
  ops_ = LinuxParser::OperatingSystem();
}

// Return the number of processes actively running on the system
int System::RunningProcesses() { 
  return LinuxParser::RunningProcesses(); 
}

//  Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses(); 
}

// Return the number of seconds since the system started running
long int System::UpTime() { 
  return LinuxParser::UpTime(); 
}