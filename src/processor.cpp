#include "processor.h"

#include <iostream>
#include <vector>

std::vector<int> ConvertProcessorAttr(std::vector<std::string> &attr) {
  std::vector<int> list {};
  for (std::string attributes : attr) {
    list.push_back(stoi(attributes));
  }
  return list;
}
std::vector<int> calculateTotal(std::vector<std::string> attr) {
    std::vector<int> attributes = ConvertProcessorAttr(attr);
    if(attributes.size() != 0){
  int usertime, nicetime, idlealltime, systemalltime, virtalltime, totaltime,
      steal;
  
  steal = attributes[LinuxParser::CPUStates::kSteal_];
  usertime = attributes[LinuxParser::CPUStates::kUser_] -
             attributes[LinuxParser::CPUStates::kGuest_];
  nicetime = attributes[LinuxParser::CPUStates::kNice_] -
             attributes[LinuxParser::CPUStates::kGuestNice_];

  idlealltime = attributes[LinuxParser::CPUStates::kIdle_] +
                attributes[LinuxParser::CPUStates::kIOwait_];
  systemalltime = attributes[LinuxParser::CPUStates::kSystem_] +
                  attributes[LinuxParser::CPUStates::kIRQ_] +
                  attributes[LinuxParser::CPUStates::kSoftIRQ_];

  virtalltime = attributes[LinuxParser::CPUStates::kGuest_] +
                attributes[LinuxParser::CPUStates::kGuestNice_];
  totaltime = usertime + nicetime + systemalltime + steal + virtalltime;

  return {totaltime, idlealltime};}
  else return {0,0};
}
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  int totalid, idled;
  float CPU_Percentage;
  std::vector<int> totaltime = calculateTotal(stringAttributes);
  int totalnonidle = totaltime[0];
  int totalidle = totaltime[1];
  //std::vector<int> prevTotalTime = calculateTotal(prevProcessorAttributes);
  //int prevTotalnonidle = prevTotalTime[0];
  //int prevIdle = prevTotalTime[1];

  //totalid = totalnonidle + totalidle - (prevTotalnonidle + prevIdle);
  totalid = totalnonidle + totalidle ;
  //idled = totalidle - prevIdle;
    idled = totalidle;
  CPU_Percentage = (float(totalid - idled)) / float(totalid);

  return CPU_Percentage;
}
void Processor::updateProcessor(){
     LinuxParser::ProcessorAttributes();
  std::vector<int> processorAttributes{};
}

