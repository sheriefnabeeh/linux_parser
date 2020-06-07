#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include <vector>

#include "linux_parser.h"
class Processor {
 public:
  Processor() {
    prevProcessorAttributes.reserve(10);
    processorAttributes.reserve(10);
    // for (int i = 0; i <= 9; i++) prevProcessorAttributes.push_back("0");
  }
  void refreshProcessor(){
      prevProcessorAttributes = stringAttributes;
      updateProcessor();
  }
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  std::vector<std::string> prevProcessorAttributes{};

  std::vector<std::string> stringAttributes =
      LinuxParser::ProcessorAttributes();
  std::vector<int> processorAttributes{};
  void updateProcessor();
};

#endif