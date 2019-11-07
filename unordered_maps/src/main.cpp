#include <iostream>
#include <chrono>
#include <cstdlib>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

struct threadPIDVector
{
  void initialize(int size);
  int getPID(int index);
  void setPID(int index, int PID);

  std::vector<int> PID_vector;
  std::mutex mutex;
};

void threadPIDVector::initialize(int size)
{
  std::lock_guard<std::mutex> guard{mutex};
  return PID_vector.assign(size, 0);
}

int threadPIDVector::getPID(int index)
{
  std::lock_guard<std::mutex> guard{mutex};
  return PID_vector.at(index);
}

void threadPIDVector::setPID(int index, int PID)
{
  std::lock_guard<std::mutex> guard{mutex};
  PID_vector.at(index) = PID;
}

threadPIDVector thread_PID_vector;

void func(int index)
{
  // std::cout << "Hello from thread" << std::endl;
  thread_PID_vector.setPID(index, static_cast<int>(getpid()));
  std::cout << "Hello from thread " << index << ", my PID is: " << thread_PID_vector.getPID(index) << std::endl;
  system("/home/michael/Documents/CODING/unordered_maps/test.sh > /dev/null &");
  std::cout << "Hello from end of thread function" << std::endl;
}

int
main(int argc, char** argv)
{

  // ********* MAP OF INTS AND STRINGS ********* //

  // Unordered map with int keys and string values:
  std::unordered_map<int, std::string> map;

  // Insert some values into the map:
  map.insert({1, "hello"});
  map.insert({3, "bye"});
  map.insert({300, "dfsedfdsf"});
  map.insert({56, "banana"});

  // Get map info:
  std::cout << "Map size: " << map.size() << std::endl;
  std::cout << "Map max_size: " << map.max_size() << std::endl;

  // Print some of the strings:
  std::cout << "Value at 1: " << map.at(1) << std::endl;

  // Iterate over the map:
  for(const auto& pair : map)
  {
    std::cout << "Value at "<< pair.first << ": " << pair.second << std::endl;
  }





  // ********* MAP OF INTS AND THREADS ********* //

  std::unordered_map<int, std::thread> map2;

  thread_PID_vector.initialize(4);

  // Insert some values into the map:
  map2.insert({1, std::thread(func, 0)});
  map2.insert({3, std::thread(func, 1)});
  map2.insert({300, std::thread(func, 2)});
  map2.insert({56, std::thread(func, 3)});

  std::this_thread::sleep_for(std::chrono::seconds(2));

  for(auto& pair : map2)
  {
    // pair.second.~thread();
    pair.second.join();
    std::cout << "Joining thread at key: " << pair.first << std::endl;
  }


  return 0;
}