#include <string>

#include "format.h"
#include <cmath>
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 

    float hrs = float(seconds)/60/60;
    float minutes = (hrs -int(hrs))*60;
    int sec = ceil((minutes- int(minutes))*60);

    return std::to_string(int(hrs)) + ":" + std::to_string(int(minutes)) + ":" + std::to_string(sec); }