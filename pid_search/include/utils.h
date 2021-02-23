#ifndef PID_SEARCH_UTILS_H
#define PID_SEARCH_UTILS_H

#include <string>


namespace pid_search
{
bool compareDirectoryCommandAndProcessCommand(const std::string& directory_entry_command,
                                              const std::string& process_name);
int findPidByCommandName(std::string command);
}

#endif
