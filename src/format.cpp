#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long times) { 
  int hours = 0; 
  int minutes = 0; 
  int seconds = 0; 
  float rest = 0.0; 
  std::ostringstream elapsedtime; 
  // hours, minutes and seconds calculations 
  hours = int(times / 3600.0); 
  rest = (times % 3600) / 60.0; // minutes and seconds left - floating number 
  minutes = int(rest); 
  seconds = int((rest - minutes) * 60);
  // string formating / padding with 0 to get HH:MM:SS
  elapsedtime << std::setfill('0') << std::setw(2) << std::right << hours 
              << ":" <<  std::setw(2) << std::right << minutes << ":" 
              << std::setw(2) << std::right << seconds;

  return elapsedtime.str(); 
}