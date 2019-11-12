#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

string formatProcName(string procName)
{
    for(int i = 0; i < procName.length(); ++i)
    {
        if(procName.at(i) == ' ')
        {
            procName.at(i) = '\00';
        }
    }
    cout << procName << endl;
    return(procName);
}

int getProcIdByName(string procName)
{
    int pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        cout << "Directory opened" << endl;
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
                ifstream cmdFile(cmdPath.c_str());
                string cmdLine;
                getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // // Keep first cmdline item which contains the program path
                    // size_t pos = cmdLine.find('\0');
                    // if (pos != string::npos)
                    //     cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    // pos = cmdLine.rfind('/');
                    // if (pos != string::npos)
                    //     cmdLine = cmdLine.substr(pos + 1);
                    // cout << "[ID]: " << id << ", [cmdLine]: " << cmdLine << endl;
                    // // Compare against requested process name
                    // if (procName == cmdLine)
                    //     pid = id;

                    // cout << "[ID]: " << id << ", [cmdLine]: " << cmdLine << endl;

                    size_t pos = cmdLine.find(procName);
                    if(pos != string::npos)
                    {
                        pid = id;
                    }
                }
            }
        }
    }

    closedir(dp);

    return pid;
}

int main(int argc, char* argv[])
{
    // Fancy command line processing skipped for brevity
    int pid = getProcIdByName(formatProcName("roslaunch enway_navigation navigation.launch"));
    cout << "pid: " << pid << endl;
    return 0;
}