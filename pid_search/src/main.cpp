#include "utils.h"

#include <iostream>
#include <string>


int
main(int argc, char** argv)
{
  std::string command {"roslaunch enway_gazebo robot_simulation.launch"};
  std::cout << "Looking for process with command: " << command << std::endl;

  int pid = pid_search::findPidByCommandName(command);
  if (pid > 0)
  {
    std::cout << "Found PID " << std::to_string(pid) << std::endl;
  }
  else
  {
    std::cout << "Did not find PID for command '" << command << "'" << std::endl;
  }

  return 0;
}
