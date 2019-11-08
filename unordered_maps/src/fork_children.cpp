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

int
main(int argc, char** argv)
{
  // Change this to choose type of loop (C++ or bash)
  Selector selector = Selector::BASH_LOOP;

  // Path to bash script to launch in children:
  std::string bash_script = "/home/michael/Documents/CODING/unordered_maps/test.sh";

  int number_of_children = 2;

  std::vector<pid_t> children_id_vector;
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
    std::cout << "\t \t \t \t \t " << static_cast<int>(pid) << std::endl;
  }

  // Start and kill child process; wait 2s before and after to give time to start and time to shutdown
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::cout << "[PARENT] \t Children are very annoying, killing" << std::endl;
  for(auto& pid : children_id_vector)
  {
    kill(pid, SIGTERM);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  return 0;
}
