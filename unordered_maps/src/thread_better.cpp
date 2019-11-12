#include <iostream>
#include <chrono>
#include <cstdlib>
#include <mutex>
#include <string>
#include <signal.h>
#include <sys/syscall.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fstream>

enum class Selector
{
  BASH_THREAD,
  CPP_THREAD,
  ROS_THREAD
};

struct threadPIDVector
{
  void initialize(int size);
  int getPID(int index);
  void setPID(int index, int PID);

  std::vector<int> PID_vector;
  std::mutex mutex;
};

void
threadPIDVector::initialize(int size)
{
  std::lock_guard<std::mutex> guard{mutex};
  return PID_vector.assign(size, -1);
}

int
threadPIDVector::getPID(int index)
{
  std::lock_guard<std::mutex> guard{mutex};
  return PID_vector.at(index);
}

void
threadPIDVector::setPID(int index, int PID)
{
  std::lock_guard<std::mutex> guard{mutex};
  PID_vector.at(index) = PID;
}

threadPIDVector thread_PID_vector;

std::unordered_map<int, std::thread> map;

bool run_threads = true;

std::string formatProcName(std::string procName)
{
  for(int i = 0; i < procName.length(); ++i)
  {
    if(procName.at(i) == ' ')
    {
        procName.at(i) = '\00';
    }
  }
  return(procName);
}

int getProcessIdByName(std::string procName)
{
  int pid = -1;

  DIR *dp = opendir("/proc");
  if (dp != NULL)
  {
    struct dirent *dirp;
    while (pid < 0 && (dirp = readdir(dp)))
    {
      int id = atoi(dirp->d_name);
      if (id > 0)
      {
        std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
        std::ifstream cmdFile(cmdPath.c_str());
        std::string cmdLine;
        getline(cmdFile, cmdLine);
        if (!cmdLine.empty())
        {
          size_t pos = cmdLine.find(procName);
          if(pos != std::string::npos)
          {
            std::cout << "Found: " << cmdLine << std::endl;

            size_t pos2 = cmdLine.find("sh\00-c");

            bool already_found = false;
            for(auto PID : thread_PID_vector.PID_vector)
            {
              if(PID == id)
              {
                already_found = true;
              }
            }

            if(pos2 == 0)
            {
              std::cout << "Is intermediary shell - rejecting" << std::endl;
            }
            else if(already_found)
            {
              std::cout << "Already found this process - rejecting" << std::endl;
            }
            else
            {
              std::cout << "Passed all checks - keeping" << std::endl;
              pid = id;
            }
          }
        }
      }
    }
  }

  closedir(dp);

  return pid;
}

void
func(const int index, const Selector selector, std::string bash_script, std::string ros_command)
{
  switch(selector)
  {
    case Selector::BASH_THREAD:
      system(bash_script.c_str());
      break;

    case Selector::CPP_THREAD:
      std::cout << "[CHILD " << index << "] \t I am a good ol' C++ loop" << std::endl;
      while(true)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "[CHILD " << index << "] \t Hello" << std::endl;
      }
      break;

    case Selector::ROS_THREAD:
      system(ros_command.c_str());
      break;
  };
  std::cout << "[CHILD " << index << "] \t Exiting" << std::endl;
}

void killProcesses()
{
  for(int i = map.size() - 1; i > -1; --i)
  {
    std::cout << "[PARENT] \t Terminating thread at key " << i << " ..." << std::endl;
    kill(thread_PID_vector.getPID(i), SIGTERM);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "[PARENT] \t Terminated thread at key " << i << std::endl;
    std::cout << "[PARENT] \t Joining thread at key " << i << " ..." << std::endl;
    map.at(i).join();
    std::cout << "[PARENT] \t Joined thread at key " << i << std::endl;
  }
}

void signalHandler(int sig)
{
  std::cout << "[HANDLER] \t Heard SIG " << sig << std::endl;
  run_threads = false;
}

int
main(int argc, char** argv)
{
  // Configs:
  int number_of_threads = 1;
  Selector selector = Selector::ROS_THREAD;
  std::string bash_script = "/home/michael/Documents/CODING/unordered_maps/test.sh";
  std::string ros_command = "roslaunch enway_gazebo robot_simulation.launch gazebo_gui:=false";

  std::cout << "[PARENT] \t Starting with PID: " << static_cast<int>(getpid()) << std::endl;

  thread_PID_vector.initialize(number_of_threads);

  for(int i = 0; i < number_of_threads; ++i)
  {
    map.insert({i, std::thread(func, i, selector, bash_script, ros_command)});
    // Wait to give to start up:
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // Get process ID by name:
    if(selector == Selector::BASH_THREAD)
    {
      thread_PID_vector.setPID(i, getProcessIdByName(formatProcName(bash_script)));
    }
    if(selector == Selector::ROS_THREAD)
    {
      thread_PID_vector.setPID(i, getProcessIdByName(formatProcName(ros_command)));
    }
    std::cout << "[CHILD " << i << "] \t Started with PID: " << thread_PID_vector.getPID(i) << std::endl;
  }

  // Register signal handler:
  signal(SIGTERM, signalHandler);
  
  while(run_threads)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  
  killProcesses();

  return 0;
}