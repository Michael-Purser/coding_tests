#include <atomic>
#include <iostream>
#include <string>
#include <thread>

namespace thread_manager
{

enum class ProcessStatus
{
  ON,
  OFF,
  FAILED,
  STARTING,
  STOPPING
};

enum class ProcessCommand
{
  NONE,
  START,
  STOP
};

class ThreadManager
{

public:
  ThreadManager(const std::string& name);
  void listen();
  void stop_listening();
  void setCommand(thread_manager::ProcessCommand command);
  void setStatus(thread_manager::ProcessStatus status);
  void startProcessThread();
  void stopProcessThread();

private:
  bool checkProcessStartedCorrectly();
  bool checkProcessStoppedCorrectly();
  std::string commandName(const thread_manager::ProcessCommand command);
  std::string statusName(const thread_manager::ProcessStatus status);

  std::atomic<ProcessCommand> command_;
  std::atomic<bool> listening_;
  std::string name_;
  std::thread process_thread_;
  std::atomic<ProcessStatus> status_;

};

} // namespace thread_manager
