#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream> // TODO: remove after done
#include <assert.h>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::cout; // TODO: remove after done
using std::endl; // TODO: remove after done

//  An example of how to read data from the filesystem
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

//  An example of how to read data from the filesystem
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

//  Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{ 
  string line;
  string key;
  string value;
  float memTotal;
  float memFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      // std::replace(line.begin(), line.end(), '=', ' ');
      // std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memTotal = stof(value);
          }
        if (key == "MemFree") {
          memFree = stof(value);
          return ((memTotal - memFree)/memTotal);
        }
      }
    }
  }
}

long LinuxParser::UpTime() 
{ 
  long uptime;
  long idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle;
  }
  return ((uptime + idle)/ sysconf(_SC_CLK_TCK));
  // return (uptime + idle); // already in secnonds
 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// REMOVE: [[maybe_unused]] once you define the function
void LinuxParser::ActiveJiffies(int pid,vector<long>& proctimes) 
{ 
  string line;
  string string1, string2, string3, string4, string5, string6, string7, string8,  \
      string9, string10, string11, string12, string13, string18, string19, string20, string21;
  long string14;
  long string15;
  long string16;
  long string17;
  long string22;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream2(line);
    while (linestream2 >> string1 >> string2 >> string3 >> string4 >> string5 >>
           string6 >> string7 >> string8 >> string9 >> string10 >> string11 >>
           string12 >> string13 >> string14 >> string15 >> string16 >>
           string17 >> string18 >> string19 >> string20 >> string21 >>
           string22) {
             proctimes.push_back(string14/sysconf(_SC_CLK_TCK));
             proctimes.push_back(string15/sysconf(_SC_CLK_TCK));
             proctimes.push_back(string16/sysconf(_SC_CLK_TCK));
             proctimes.push_back(string17/sysconf(_SC_CLK_TCK));
             proctimes.push_back(string22/sysconf(_SC_CLK_TCK));
       return;
    }
  }
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string key;
  string line;
  string cpu;
  string user;
  string nice;
  string system;
  string idle;
  string iowait;
  string irq;
  string softirq;
  string steal;
  string guest;
  string guest_nice;

  vector<string> procstat;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> cpu >> user >> nice >> system >> idle >> iowait >>
           irq >> softirq >> steal >> guest >> guest_nice) {
      if (cpu == "cpu") {
        procstat.push_back(user);
        procstat.push_back(nice);
        procstat.push_back(system);
        procstat.push_back(idle);
        procstat.push_back(iowait);
        procstat.push_back(irq);
        procstat.push_back(softirq);
        procstat.push_back(steal);
        procstat.push_back(guest);
        procstat.push_back(guest_nice);
        return procstat;
      }
    }
  }
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string meminfo;
  string key;
  int value;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string meminfo;
  string key;
  int value;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  } 
}

// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line); 
    return line;
    }
}

// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) 
{ 
  string key;
  long value;
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize") {
          return to_string((value/1000));
        }
      }
    }
  } 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) 
{ 
  return string(); 
}

// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{
  string key;
  int value;
  int uid;
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          uid = value;
        }
      }
    }
  }

  string user;
  string perm;
  int uid2;
  // find the associated user 
  std::ifstream filestream2(kPasswordPath);
  if (filestream2.is_open()) {
    while (std::getline(filestream2, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream2(line);
      while (linestream2 >> user >> perm >> uid2) {
        // if (uid2.compare(uid) == 0) {
        if (uid == uid2) {
          return user;
          // return to_string(uid);
        }
      }
    }
  }
}

# if 0
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime() {
  string line;
  long uptime;
  long idletime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream2(line);
    while (linestream2 >> uptime >> idletime) {
      return (uptime);  // already in seconds
    }
  }
}
#endif