#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

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
    vector<long> proctimes;
    LinuxParser::ActiveJiffies(this->Pid(), proctimes);
    // utime + stime
    long totaltime = proctimes[0] + proctimes[1];  
    // seconds = uptime - (starttime / Hertz)
    long seconds = Process::UpTime() - proctimes[4];
    // cpu_usage = 100 * ((total_time / Hertz) / seconds)
    cpuUtil_ = (totaltime/seconds);

    return cpuUtil_; 
}

void Process::setCpuUtil(float cpuUtil)
{
    cpuUtil_ = cpuUtil;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this->Pid()); 
}

void Process::setUser(std::string user)
{
    user_ = user;
}


// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return LinuxParser::Ram(this->Pid()); 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{
    int pid = this->Pid();
    user_ = LinuxParser::User(pid);
    return user_;    
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
    return(LinuxParser::UpTime()); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }