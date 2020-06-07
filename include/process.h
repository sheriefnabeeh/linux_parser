#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    Process(int pid):pid_(pid){}
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process & a) ;  // TODO: See src/process.cpp
  long int UserId();
  // TODO: Declare any necessary private members
 private:
 int pid_;
 std::string Uid_ = LinuxParser::Uid(pid_);
 std::string user_ = LinuxParser::User(Uid_);
 std::string command_ = LinuxParser::Command(pid_) ;
 float utilization_ = LinuxParser::processCpuUtilization(pid_);
 std::string ram_ =  LinuxParser::Ram(pid_);
 long int uptime_ = LinuxParser::UpTime() - LinuxParser::UpTime(pid_);

};

#endif