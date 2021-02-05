#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream> 

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// constructor 
Process::Process(int pid) {
  pid_ = pid;
  SetCommand(); 
  SetUser(); 
};


// TODO: Return this process's ID
int Process::Pid() const { 
  return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() const { 
  return cmd_; 
}

void Process::SetCommand(){
  cmd_ = LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() const { 
  return user_; 
}

void Process::SetUser() { 
  user_ = LinuxParser::User(pid_);  
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }