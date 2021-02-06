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

// Return this process's CPU utilization
float Process::CpuUtilization() { 
  // get cpu used by process 
  string info;
  // processes executing 
  vector<string> ptimers; 
  // all timers
  unsigned long int utime, stime, cutime, cstime;
  unsigned long int starttime; 
  // CONST : hertz  
  unsigned long int nb_ticksec = sysconf(_SC_CLK_TCK);
  // res 
  unsigned long int total_time = 0;
  // calculation
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, info, ' ')){
      ptimers.push_back(info); 
    }
  }
  
  total_time = std::stoul(ptimers[13]) + std::stoul(ptimers[14]) + std::stoul(ptimers[15]) + std::stoul(ptimers[16]); 
  return 0.17; 
}

// TODO: Return the command that generated this process
string Process::Command() const { 
  return cmd_; 
}

void Process::SetCommand(){
  cmd_ = LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  long int vram; 
  short unsigned int counter = 0;
  short unsigned int precision = 2; 
  bool floating_part = false; 
  std::ostringstream s_vram; 
  vram = std::stol(LinuxParser::Ram(Pid()));
  for (char const& c : to_string(vram / float(1000))) {
    s_vram << c; 
    // handling floating part to a fixed limit 
    if ( c == '.') {
      floating_part = true; 
    }
    if (floating_part) {
      if (counter < precision){
        counter += 1; 
      } else {
        break;
      }
    }
  }          
  return s_vram.str();
}

// Return the user (name) that generated this process
string Process::User() const { 
  return user_; 
}

void Process::SetUser() { 
  user_ = LinuxParser::User(Pid());  
}

// Return the age of this process (in seconds)
long int Process::UpTime() { 
  // Uptime is the time in second where process was born 
  return int(LinuxParser::UpTime(Pid()));
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }