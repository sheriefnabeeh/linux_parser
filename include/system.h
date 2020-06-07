#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System() { createProcesses();
  Processor();
   }
  void refreshSystem() {
    createProcesses();
    sortProcesses();
    updateMem();
    updateTotalPrcs();
    updateRunPrcs();
    updateUptTime();
    updateProcessor();
    cpu_.refreshProcessor();
  }
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  void createProcesses();
  void sortProcesses();
  Processor cpu_ = Processor();
  std::vector<Process> processes_ = {};
  std::string kernal_ = LinuxParser::Kernel();
  float memory_util = LinuxParser::MemoryUtilization();
  int total_processes_ = LinuxParser::TotalProcesses();
  int running_processes_ = LinuxParser::RunningProcesses();
  std::string OS = LinuxParser::OperatingSystem();
  long upTime = LinuxParser::UpTime();

  // private setters to updateValues of System object
  void updateMem();
  void updateTotalPrcs();
  void updateRunPrcs();
  void updateUptTime();
  void updateProcessor();
};

#endif