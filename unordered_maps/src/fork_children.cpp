#include <iostream>
#include <chrono>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

enum class Selector
{
  CPP_LOOP,
  BASH_LOOP
};

// Global vector, needed for the signal handler
std::vector<pid_t> children_id_vector;

// Global variable to set when program should terminate
bool terminate = false;

void
signalHandler(int sig)
{
  std::cout << "[HANDLER] \t Heard signal with id: " << sig << std::endl;
  std::cout << "[HANDLER] \t Children are very annoying, killing" << std::endl;
  for(auto& pid : children_id_vector)
  {
    kill(pid, SIGTERM);
    std::cout << "[HANDLER] \t Killed PID: \t " << static_cast<int>(pid) << std::endl;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  terminate = true;
}

int
main(int argc, char** argv)
{
  // Change this to choose type of loop (C++ or bash)
  Selector selector = Selector::BASH_LOOP;

  // Path to bash script to launch in children:
  std::string bash_script = "/home/michael/Documents/CODING/unordered_maps/test.sh";

  int number_of_children = 2;

  children_id_vector.assign(number_of_children, -1);

  for(int i=0; i<number_of_children; i++)
  {
    // Child processes
    if((children_id_vector.at(i) = fork()) == 0)
    {
      // These prints show that child has access to its own PID and that of its parent
      std::cout << "[CHILD " << i + 1 << "] \t Parent PID: \t \t " << static_cast<int>(getppid()) << std::endl;
      std::cout << "[CHILD " << i + 1 << "] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
      std::cout << "[CHILD " << i + 1 << "] \t PID from fork: \t " << static_cast<int>(children_id_vector.at(i)) << std::endl;

      switch(selector)
      {
      case Selector::CPP_LOOP:
        std::cout << "[CHILD " << i + 1 << "] \t I am a good ol' C++ loop" << std::endl;
        while(true)
        {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "[CHILD " << i + 1 << "] \t Hello" << std::endl;
        }
        break;

      case Selector::BASH_LOOP:
        execl(bash_script.c_str(),bash_script.c_str(), NULL);
        break;
      }
    }
  }
  
  // Parent process

  // These prints show that parent has access to its own PID and to that of child
  std::cout << "[PARENT] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
  std::cout << "[PARENT] \t Children PIDs:" << std::endl;
  for(auto& pid : children_id_vector)
  {
    std::cout << " \t \t \t \t \t " <<static_cast<int>(pid) << std::endl;
  }

  // Register signal handler
  signal(SIGTERM, signalHandler);

  // Wait in loop
  while(!terminate)
  {
    std::cout << "[PARENT] \t Listening to children" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << "[PARENT] \t Can go to sleep now" << std::endl;

  return 0;
}
