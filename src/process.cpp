#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{ 
    return pid_; 
}

// set the process id
void Process::setPid(int pid)
{
    pid_ = pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    return cpuUtil_; 
}

void Process::setCpuUtil(float cpuUtil)
{
    cpuUtil_ = cpuUtil;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return user_; 
}

void Process::setUser(std::string user)
{
    user_ = user;
}


// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }