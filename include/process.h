#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int p); 
  int Pid() const;                               
  std::string User() const;                      
  void SetUser(); 
  std::string Command() const;                   
  void SetCommand();
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // Declare any necessary private members
 private:
  std::string user_ = ""; 
  std::string cmd_ = ""; 
  int pid_; 
};

#endif