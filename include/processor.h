#include <vector> 
#include <string>

#ifndef PROCESSOR_H
#define PROCESSOR_H



class Processor {
 public: 
  Processor (); // constructor
  float Utilization(); 
  float Instant_Utilization(); 
  
  // Setters : take Linux parser string, then
  // convert to unsigned long long int and set private members 
  void IdleTime(std::vector<std::string> cpuse); // 
  unsigned long long int IdleTime() const; 
  void RunningTime(std::vector<std::string> cpuse); 
  unsigned long long int RunningTime() const; 
  void SetTotalTime(); 
  unsigned long long int TotalTime() const; 

 private:
  unsigned long long int idle_time_ = 0; 
  unsigned long long int running_time_ = 0; 
  unsigned long long int total_time_ = 0; 
  // same private members but for instant cpu usage : delta  
  unsigned int d_idle_time_ = 0; 
  unsigned int d_running_time_ = 0; 
  unsigned int d_total_time_ = 0; 
  // First init 
  bool init_time = true; 
};

#endif