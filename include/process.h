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
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

  // Declare any necessary private members
 private:
  std::string user_ = ""; 
  std::string cmd_ = ""; 
  int pid_; 
  float cpusage_ = 0.0; 
};

#endif