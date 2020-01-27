#include "../include/thread_manager.h"
#include <chrono>

int main(int argc, char** argv)
{
  thread_manager::ThreadManager manager1("thread_1");
  thread_manager::ThreadManager manager2("thread_2");
  
  std::thread manager1_thread(&thread_manager::ThreadManager::listen, &manager1);
  std::thread manager2_thread(&thread_manager::ThreadManager::listen, &manager2);

  std::this_thread::sleep_for(std::chrono::seconds(2));
  manager1.setCommand(thread_manager::ProcessCommand::START);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  manager2.setCommand(thread_manager::ProcessCommand::START);

  std::this_thread::sleep_for(std::chrono::seconds(5));
  manager1.setCommand(thread_manager::ProcessCommand::STOP);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  manager2.setCommand(thread_manager::ProcessCommand::STOP);

  std::this_thread::sleep_for(std::chrono::seconds(2));
  manager1.stop_listening();
  manager2.stop_listening();

  manager1_thread.join();
  manager2_thread.join();
}
