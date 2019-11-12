#include <iostream>
#include <iterator>
#include <chrono>
#include <signal.h>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

enum class Selector
{
  CPP_LOOP,
  BASH_LOOP,
  ROS_PROCESS
};

std::vector<std::string>
extractCommandParts(std::string command)
{
  std::istringstream iss(command);
  std::vector<std::string> command_parts{std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>{}};
  return command_parts;
}

const char**
formatCommand(std::string command)
{
  std::vector<std::string> command_parts = extractCommandParts(command);
  const char** arguments = new const char*[command_parts.size() + 1];
  for(int i = 0; i < command_parts.size(); ++i)
  {
    arguments[i] = command_parts.at(i).c_str();
    std::cout << "Arg at [" << i << "]: \t " << arguments[i] << std::endl;
  }
  arguments[command_parts.size()] = NULL;
  return arguments;
}

int
main(int argc, char** argv)
{
  // Change this to choose type of loop (C++ or bash)
  Selector selector = Selector::ROS_PROCESS;

  // Path to bash script OR ros command to launch in child:
  std::string bash_script = "/home/michael/Documents/CODING/unordered_maps/test.sh";
  std::string command = "roslaunch enway_navigation navigation.launch";


  pid_t pid = fork();
  
  // Child process
  if(pid == 0)
  {
    // These prints show that child has access to its own PID and that of its parent
    std::cout << "[CHILD] \t Parent PID: \t \t " << static_cast<int>(getppid()) << std::endl;
    std::cout << "[CHILD] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
    std::cout << "[CHILD] \t PID from fork: \t " << static_cast<int>(pid) << std::endl;

    switch(selector)
    {
      case Selector::CPP_LOOP:
        std::cout << "[CHILD] \t I am a good ol' C++ loop" << std::endl;
        while(true)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
          std::cout << "[CHILD] \t Hello" << std::endl;
        }
        break;

      case Selector::BASH_LOOP:
        execl(bash_script.c_str(),bash_script.c_str(), NULL);
        break;
      
      case Selector::ROS_PROCESS:
        std::vector<std::string> command_parts = extractCommandParts(command);
        const char** arguments = new const char*[command_parts.size() + 1];
        for(int i = 0; i < command_parts.size(); ++i)
        {
          arguments[i] = command_parts.at(i).c_str();
          std::cout << "Arg at [" << i << "]: \t " << arguments[i] << std::endl;
        }
        arguments[command_parts.size()] = NULL;
        execvp(extractCommandParts(command).front().c_str(), (char**)arguments);
        break;
    }
  }
  
  // Parent process
  else
  {
    // These prints show that parent has access to its own PID and to that of child
    std::cout << "[PARENT] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
    std::cout << "[PARENT] \t Child PID: \t \t " << static_cast<int>(pid) << std::endl;
    
    // Start and kill child process; wait 2s before and after to give time to start and time to shutdown
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::cout << "[PARENT] \t Child is annoying, killing " << std::endl;
    kill(pid, SIGTERM);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }

  return 0;
}
