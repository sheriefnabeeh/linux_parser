#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "system.h"
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

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float free_mem, total_mem;
  string line;
  string key, value;
  std::ifstream fileStream{kProcDirectory + kMeminfoFilename};

  if (fileStream.is_open()) {
    while (std::getline(fileStream, line)) {
      {
        std::istringstream stringStream(line);
        stringStream >> key >> value;
        if (key == "MemTotal:") total_mem = stoi(value);

        if (key == "MemFree:") free_mem = stoi(value);
      }
    }
  }
  return (total_mem - free_mem) / total_mem;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string value, key, line;
  std::ifstream fileStream{kProcDirectory + kUptimeFilename};
  if (fileStream.is_open()) {
    while (std::getline(fileStream, line)) {
      std::istringstream stream{line};
      stream >> value >> key;
    }
  }
  long val;
  // try {
  val = stol(value);
  //} catch (std::invalid_argument) {
  //  std::cout << "error with value";
  //}
  // trace before return

  return val;
}
vector<std::string> LinuxParser::ProcessorAttributes() {
  string key, line, usertime, guest, nicetime, guestnice, idletime, ioWait,
      systemtime, irq, softIrq, steal;
  vector<string> attr{};
  std::ifstream fileStream{kProcDirectory + kStatFilename};
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream stream{line};
    stream >> key;

    stream >> usertime;
    attr.push_back(usertime);
    stream >> nicetime;
    attr.push_back(nicetime);
    stream >> systemtime;
    attr.push_back(systemtime);
    stream >> idletime;
    attr.push_back(idletime);
    stream >> ioWait;
    attr.push_back(ioWait);
    stream >> irq;
    attr.push_back(irq);
    stream >> softIrq;
    attr.push_back(softIrq);
    stream >> steal;
    attr.push_back(steal);
    stream >> guest;
    attr.push_back(guest);
    stream >> guestnice;
    attr.push_back(guestnice);
  }
  return attr;
}
// TODO: Read and return CPU utilization

vector<int> LinuxParser::processTime(int pid) {
  string key, value, line;
  vector<int> times;
  std::ifstream fileStream{kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename};
  if (fileStream.is_open()) {
    //    std::getline(fileStream, line);
    std::getline(fileStream, line);
    std::istringstream stream{line};
    for (int i = 0; i <= 12; i++) stream >> key;
    stream >> value;
    times.push_back(stoi(value));
    stream >> value;
    times.push_back(stoi(value));
    stream >> value;
    times.push_back(stoi(value));
    stream >> value;
    times.push_back(stoi(value));
    for (int i = 0; i <= 3; i++) stream >> key;
    stream >> value;
    times.push_back(stoi(value));
  }
  return times;
}
float LinuxParser::processCpuUtilization(int pid) {
  vector<int> pTimes = processTime(pid);
  float total_time = float((pTimes[0] + pTimes[1] + pTimes[2] + pTimes[3])) /
                     sysconf(_SC_CLK_TCK);
  float total_elapsed =
      LinuxParser::UpTime() - (pTimes[4] / sysconf(_SC_CLK_TCK));
  float util = (total_time / total_elapsed);
  return util;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string key, value, line;
  int processes;
  std::ifstream fileStream{kProcDirectory + kStatFilename};
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    while (std::getline(fileStream, line)) {
      std::istringstream stream{line};
      stream >> key >> value;
      if (key == "processes") {
        processes = stoi(value);
      }
    }
  }
  return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key, value, line;
  int processes;
  std::ifstream fileStream{kProcDirectory + kStatFilename};
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    while (std::getline(fileStream, line)) {
      std::istringstream stream{line};
      stream >> key >> value;
      if (key == "procs_running") {
        processes = stoi(value);
      }
    }
  }
  return processes;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) {
  string key, value, line, Uid;
  std::ifstream fileStream{kProcDirectory + "/" + std::to_string(pid) +
                           kCmdlineFilename};
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) {
  string key, value, line;
  string ram;
  string comp = "VmSize:";
  std::ifstream fileStream{kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename};
  if (fileStream.is_open()) {
    while (std::getline(fileStream, line)) {
      std::istringstream stream{line};
      stream >> key >> value;
      if (key == comp) {
        ram = value;
      }
    }
  }
  int r = 0;
  try {
   if(ram != "")
    r = stoi(ram) / 1000;
  } catch (std::invalid_argument& s) {
    std::cout << "wrong input"
              << "\n";
  }
  return std::to_string(r);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string key, value, line, Uid;
  string comp = "Uid:";
  std::ifstream fileStream{kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename};
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    while (std::getline(fileStream, line)) {
      std::istringstream stream{line};
      stream >> key >> value;
      if (key == comp) {
        Uid = value;
      }
    }
  }
  return Uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(std::string Uid) {
  string key, val, user, line;
  std::fstream filestream{kPasswordPath};

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream strStream{line};
      strStream >> key >> val >> val;
      ;
      if (val == Uid) user = key;
    }
  }
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  vector<int> ptimes = processTime(pid);
  return ptimes[4] / sysconf(_SC_CLK_TCK);
}