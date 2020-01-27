#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <iostream>


bool
compareDirectoryCommandAndProcessCommand(const std::string& directory_entry_command,
                                         const std::string& process_name)
{
  const size_t position = directory_entry_command.find(process_name);
  if(position != std::string::npos)
  {
    const size_t shell_prefix_position = directory_entry_command.find("sh\00-c");
    if(shell_prefix_position != 0)
    {
      return true;
    }
  }
  return false;
}

int
findPidByCommandName(std::string command)
{ 
  int pid = -1;

  std::replace(command.begin(), command.end(), ' ', '\00');

  const std::string search_directory = "/proc/";
  const std::string process_command_line_file = "/cmdline";
  
  for (auto& directory_entry: std::filesystem::directory_iterator(search_directory))
  {
    std::string file_contents;
    std::ifstream file_path((directory_entry.path().string() + process_command_line_file).c_str());
    getline(file_path, file_contents);
    if(pid<=0 && compareDirectoryCommandAndProcessCommand(file_contents, command))
    {
      std::cout << "Found process in " << directory_entry.path().string()  << std::endl;
      std::cout << "Command: " << file_contents << std::endl;
      std::cout << directory_entry.path().filename() << std::endl;
      try
      {
        pid = std::stoi(directory_entry.path().filename());
      }
      catch (const std::exception&)
      {
        std::cout << "Folder name conversion error - not adapting PID";
      }
    }
  }

  return pid;
}

int main(int argc, char* argv[])
{
  const std::string command = "roslaunch enway_gazebo robot_simulation.launch";
 
  std::cout << "Looking for process with command" << command << std::endl;
  int pid = findPidByCommandName(command);
  if(pid > 0)
  {
    std::cout << "Found PID " << std::to_string(pid) << std::endl;
  }
  else
  {
    std::cout << "Did not find PID for command '" << command << "'" << std::endl;
  }
}
