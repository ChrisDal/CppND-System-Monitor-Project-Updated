#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  // simple memory used calculation 
  // % mem used  = total mem - mem free 
  string line;
  string key;
  string value;
  string ksize;
  float memtotal = 0.0; 
  float memfree = 0.0;
  float memused = 1.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> ksize) {
        if (key == "MemTotal") {
          memtotal = stof(value);
        } else if (key == "MemFree") {
          memfree = stof(value); 
        };
      };
    };
  };
  if (memtotal != 0.0) {
    memused = (memtotal - memfree) /  memtotal; 
  }
  return memused; 
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  // get time running  
  string line;
  string ktime;
  string kidle;
  long timespent = 0; 
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> ktime >> kidle;
    timespent = std::stol(ktime);
  }
  return timespent; 
}

/*
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }
*/ 

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  // get cpu used 
  string line;
  // first word 
  string word; 
  // processes executing 
  string user, nice, systm; 
  // "idle"
  string idle, iowait, steal;
  // servicing : interuption and soft interuption 
  string irq, softirq; 
  // running 
  string guest, guest_nice;
  // res
  vector<string> cpuse; 
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> word >> user >> nice >> systm >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    if (word == "cpu") {
      cpuse = {user, nice, systm, idle, iowait, irq, softirq, steal, guest, guest_nice};
    }
  }
  return cpuse; 
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  // total processes numbers 
  string line;
  string key;
  string value;
  int nbpro = 0.0; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          nbpro = stoi(value);
          
        }
      }
    }
  }
  return nbpro; 
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  // get the number of running process 
  string line;
  string key;
  string value;
  int nbpro_run = 0.0; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "proc_running") {
          nbpro_run = stoi(value);
          
        }
      }
    }
  }
  return nbpro_run; 
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  // get the command line for PID 
  string line;
  string cmd; 
  std::ifstream stream(kProcDirectory + to_string(pid) +kCmdlineFilename);
  if (stream.is_open()) {
    // handling NULL TERM character
    while (std::getline(stream, line, '\0')){
      std::replace(line.begin(), line.end(), '\n', ' ');
      cmd += line;
      cmd += " ";
    }
  }
  // remove last space 
  return cmd.substr(0, cmd.size()-1);
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  // get the ram used by the process 
  string line;
  string key;
  string value;
  string other;
  string vram; 
  // Reading File 
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> other) {
        if (key == "VmSize") {
          vram = value;
        }
      }
    }
  }
  return vram; 
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value;
  string other;
  string uid; 
  std::ifstream filestream(kProcDirectory + to_string(pid) +  kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> other) {
        if (key == "Uid") {
          uid = value;
        }
      }
    }
  }
  return uid; 
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string line;
  string key;
  string value;
  string other;
  string matching_uid; 
  string other_too; 
  string user; 
  // get uid 
  string uid = LinuxParser::Uid(pid); 
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> other >> matching_uid >> other_too ) {
        if (uid == matching_uid) {
          user = key;
        }
      }
    }
  }
  return user; 
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  long uptime = 0; 
  std::vector<string> sline; 
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line, ' ')){
      sline.push_back(line); 
    }
  } 
  uptime = std::stol(sline[20]); 
  return uptime / float(sysconf(_SC_CLK_TCK)) ; 
}