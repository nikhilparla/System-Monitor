#include "processor.h"
#include <vector>
#include <string>

#include "linux_parser.h"


using std::vector;
using std::string;


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
/*
user: normal processes executing in user mode
nice: niced processes executing in user mode
system: processes executing in kernel mode
idle: twiddling thumbs
iowait: In a word, iowait stands for waiting for I/O to complete. But there are several problems:
    Cpu will not wait for I/O to complete, iowait is the time that a task is waiting for I/O to complete. When cpu goes into idle state for outstanding task io, another task will be scheduled on this CPU.
    In a multi-core CPU, the task waiting for I/O to complete is not running on any CPU, so the iowait of each CPU is difficult to calculate.
    The value of iowait field in /proc/stat will decrease in certain conditions. So, the iowait is not reliable by reading from /proc/stat.
irq: servicing interrupts
softirq: servicing softirqs
steal: involuntary wait
guest: running a normal guest
guest_nice: running a niced guest
*/
    vector<string> cpuinfo = LinuxParser::CpuUtilization();
    float usertime      = stof(cpuinfo[0]);
    float nicetime      = stof(cpuinfo[1]);
    float systemtime    = stof(cpuinfo[2]);
    float idletime      = stof(cpuinfo[3]);
    float ioWait        = stof(cpuinfo[4]);
    float irq           = stof(cpuinfo[5]);
    float softirq       = stof(cpuinfo[6]);
    float steal         = stof(cpuinfo[7]);
    float guest         = stof(cpuinfo[8]);
    float guest_nice    = stof(cpuinfo[9]);

    usertime = usertime - guest;
    nicetime = nicetime - guest_nice;  
    float idlealltime = idletime + ioWait;
    float systemalltime = systemtime + irq + softirq;
    float virtalltime = guest + guest_nice;
    float totaltime = usertime + nicetime + systemalltime + idlealltime + steal + virtalltime;

    PrevIdle = prev_idletime + prev_ioWait;
    float Idle = idletime + ioWait;

    PrevNonIdle = prev_usertime + prev_nicetime + prev_systemtime + prev_irq + prev_softirq +  prev_steal;
    float NonIdle = usertime + nicetime + systemtime + irq + softirq + steal;

    PrevTotal = PrevIdle +  PrevNonIdle;
    totaltime = Idle + NonIdle;

    float totald = totaltime - PrevTotal;
    float idled = idletime - PrevIdle;

    float cpu_percentage = (totald - idled)/totald;

    // copy the prev values
    prev_usertime = usertime;
    prev_nicetime = nicetime ;
    prev_systemtime = systemtime;
    prev_idletime = idletime;
    prev_ioWait = ioWait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;
                                               
    return cpu_percentage; 
}