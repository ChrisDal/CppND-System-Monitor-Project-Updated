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
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  
  // Getters and setters
  
  // set and get kernel 
  void SetKernel();
  std::string Kernel() const;        
  // OS 
  void SetOps();
  std::string OperatingSystem() const;     
  
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string kernel_; 
  std::string ops_;
};

#endif