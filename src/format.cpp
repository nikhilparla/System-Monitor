#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    int hours;
    int minutes;
    int secs;
    hours = seconds/3600;
    
    minutes = seconds % 3600;
    minutes = minutes/60;
    
    secs = seconds % 60;

    return (std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(secs)); 
}

