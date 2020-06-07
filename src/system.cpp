#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

void System::createProcesses() {
  // create Processes according to size of LinuxParser::Pids
  // inside the loop, assign the Pid, User, Command, Utiliza.. , ....
  // remove  process in case not found again (and destroy object)
  processes_.clear();
  for (int pid : LinuxParser::Pids()) {
    Process process{pid};
    processes_.push_back(process);
  }
}
// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernal_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return memory_util; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return OS; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return running_processes_; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return total_processes_; }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { return upTime; }

bool compare(Process& a, Process& b) { return a < b; }
void System::sortProcesses() {
  std::sort(processes_.begin(), processes_.end(), compare);
}
 
void System::updateMem() {memory_util =LinuxParser::MemoryUtilization();}
void System::updateTotalPrcs() {total_processes_ = LinuxParser::TotalProcesses();}
void System::updateRunPrcs() {running_processes_ = LinuxParser::RunningProcesses();}
void System::updateUptTime() {upTime = LinuxParser::UpTime(); }
void System::updateProcessor() {}