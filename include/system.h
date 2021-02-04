#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System(); 
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  
  // Getters and setters
  
  // set and get kernel 
  void SetKernel();
  std::string Kernel() const;         // TODO: See src/system.cpp
  
  // OS 
  void SetOps();
  std::string OperatingSystem() const;      // TODO: See src/system.cpp
  
  
  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string kernel_; 
  std::string ops_;
};

#endif