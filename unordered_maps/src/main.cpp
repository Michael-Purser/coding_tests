#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

void func()
{
  std::cout << "Hello from thread" << std::endl;
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

  // Insert some values into the map:
  map2.insert({1, std::thread(func)});
  map2.insert({3, std::thread(func)});
  map2.insert({300, std::thread(func)});
  map2.insert({56, std::thread(func)});

  for(auto& pair : map2)
  {
    pair.second.join();
    std::cout << "Joining thread at key: " << pair.first << std::endl;
  }


  return 0;
}