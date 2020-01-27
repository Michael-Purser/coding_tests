# include "../include/thread_manager.h"
# include <chrono>

thread_manager::ThreadManager::ThreadManager(const std::string& name)
{
  listening_ = true;
  name_ = name;
  setCommand(ProcessCommand::NONE);
  setStatus(ProcessStatus::OFF);
}

void
thread_manager::ThreadManager::listen()
{
  std::cout << name_ << ": Starting listener" << std::endl;
  while(listening_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (command_ == ProcessCommand::START)
    {
      std::cout << name_ << ": Received command: " << commandName(ProcessCommand::START) << std::endl;
      startProcessThread();
    }
    if (command_ == ProcessCommand::STOP)
    {
      std::cout << name_ << ": Received command: " << commandName(ProcessCommand::STOP) << std::endl;
      stopProcessThread();
    }
  }
  std::cout << name_ << ": Stopping listener" << std::endl;
}

void
thread_manager::ThreadManager::stop_listening()
{
  listening_ = false;
}

void
thread_manager::ThreadManager::startProcessThread()
{
  setCommand(ProcessCommand::NONE);
  if(status_ == ProcessStatus::STARTING || status_ == ProcessStatus::ON || status_ == ProcessStatus::FAILED)
  {
    std::cout << name_ << ": Process already started - not starting" << std::endl;
    return;
  }
  setStatus(ProcessStatus::STARTING);

  std::this_thread::sleep_for(std::chrono::seconds(3)); // Dummy waiter

  if(checkProcessStartedCorrectly())
  {
    setStatus(ProcessStatus::ON);
    return;
  }
  setStatus(ProcessStatus::FAILED);
  return;
}

void
thread_manager::ThreadManager::stopProcessThread()
{
  setCommand(ProcessCommand::NONE);
  if(status_ == ProcessStatus::STOPPING || status_ == ProcessStatus::OFF)
  {
    std::cout << name_ << ": Process already stopped - not stopping" << std::endl;
    return;
  }
  setStatus(ProcessStatus::STOPPING);

  std::this_thread::sleep_for(std::chrono::seconds(1)); // Dummy waiter

  if(checkProcessStoppedCorrectly())
  {
    setStatus(ProcessStatus::OFF);
    return;
  }
  setStatus(ProcessStatus::FAILED);
  return;
}

bool
thread_manager::ThreadManager::checkProcessStartedCorrectly()
{
  return true;
}

bool
thread_manager::ThreadManager::checkProcessStoppedCorrectly()
{
  return true;
}

std::string
thread_manager::ThreadManager::commandName(const thread_manager::ProcessCommand command)
{
  switch (command)
  {
    case ProcessCommand::NONE: return "NONE";
    case ProcessCommand::START: return "START";
    case ProcessCommand::STOP: return "STOP";
    default: return "(command not recognized)";
  }
}

std::string
thread_manager::ThreadManager::statusName(const thread_manager::ProcessStatus status)
{
  switch (status)
  {
    case ProcessStatus::ON: return "ON";
    case ProcessStatus::OFF: return "OFF";
    case ProcessStatus::FAILED: return "FAILED";
    case ProcessStatus::STARTING: return "STARTING";
    case ProcessStatus::STOPPING: return "STOPPING";
    default: return "(status not recognized)";
  }
}

void
thread_manager::ThreadManager::setCommand(thread_manager::ProcessCommand command)
{
  command_ = command;
}

void
thread_manager::ThreadManager::setStatus(thread_manager::ProcessStatus status)
{
  status_ = status;
  std::cout << name_ << ": Status: " << statusName(status_) << std::endl;
}
