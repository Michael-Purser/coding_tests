#include <iostream>
#include <chrono>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <utility> //
#include <vector>

enum class Selector
{
  CPP_LOOP,
  BASH_LOOP
};




// Change this to choose type of loop (C++ or bash)
Selector selector = Selector::BASH_LOOP;

// Path to bash script to launch in children:
std::string bash_script = "/home/michael/Documents/CODING/unordered_maps/test.sh";

// Global vector, needed for the signal handler
std::unordered_map<int, pid_t> children_map;

// Global variable to set when program should terminate
bool terminate = false;




void
childFunction(int ID)
{
  // These prints show that child has access to its own PID and that of its parent
  std::cout << "[CHILD " << ID + 1 << "] \t Parent PID: \t \t " << static_cast<int>(getppid()) << std::endl;
  std::cout << "[CHILD " << ID + 1 << "] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
  std::cout << "[CHILD " << ID + 1 << "] \t PID from fork: \t " << static_cast<int>(children_map.at(ID)) << std::endl;

  switch(selector)
  {
  case Selector::CPP_LOOP:
    std::cout << "[CHILD " << ID + 1 << "] \t I am a good ol' C++ loop" << std::endl;
    while(true)
    {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[CHILD " << ID + 1 << "] \t Hello" << std::endl;
    }
    break;

  case Selector::BASH_LOOP:
    execl(bash_script.c_str(),bash_script.c_str(), NULL);
    break;
  }
}

void
createChildByID(int ID)
{
  children_map.insert_or_assign(ID, fork());
  if(children_map.at(ID) == 0)
  {
    childFunction(ID);
  }
  std::cout << "[PARENT] \t Created PID: \t " << static_cast<int>(children_map.at(ID)) << std::endl;
}

void
killChildByID(int ID)
{
  kill(children_map.at(ID), SIGTERM);
  std::cout << "[PARENT] \t Killed PID: \t " << static_cast<int>(children_map.at(ID)) << std::endl;
}

void
signalHandler(int sig)
{
  std::cout << "[HANDLER] \t Heard signal with id: " << sig << std::endl;
  std::cout << "[HANDLER] \t Called from PID: " << static_cast<int>(getpid()) << std::endl;
  std::cout << "[HANDLER] \t Children are very annoying, killing" << std::endl;
  for(auto& child : children_map)
  {
    killChildByID(child.first);
  }
  
  std::cout << "[HANDLER] \t All children are dead" << std::endl;
  terminate = true;
}

void
restartChildByID(int ID)
{
  std::cout << "[PARENT] \t Restarting PID: \t " << static_cast<int>(children_map.at(ID)) << std::endl;
  killChildByID(ID);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  createChildByID(ID);
  std::cout << "[PARENT] \t Restarted PID: \t " << static_cast<int>(children_map.at(ID)) << std::endl;
}

void
parentFunction()
{
  // These prints show that parent has access to its own PID and to that of child
  std::cout << "[PARENT] \t PID: \t \t \t " << static_cast<int>(getpid()) << std::endl;
  std::cout << "[PARENT] \t Children PIDs:" << std::endl;
  for(auto& pid : children_map)
  {
    std::cout << " \t \t \t \t \t " <<static_cast<int>(pid.second) << std::endl;
  }

  // Kill a child by ID
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  killChildByID(0);

  // Create a child by ID
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  createChildByID(2);

  // Create a child by ID
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  createChildByID(3);

  // Restart a child by ID
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  restartChildByID(3);

  // Wait in loop
  while(!terminate)
  {
    std::cout << "[PARENT] \t Listening to children" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << "[PARENT] \t Can go to sleep now" << std::endl;
}

int
main(int argc, char** argv)
{
  int number_of_children = 2;

  // Register signal handler
  signal(SIGTERM, signalHandler);

  // Children
  for(int ID=0; ID<number_of_children; ID++)
  {
    createChildByID(ID);
  }
  
  // Parent process
  parentFunction();

  return 0;
}
