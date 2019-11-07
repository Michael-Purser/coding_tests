#include <iostream>
#include <memory>
#include <vector>

#include "../include/Position.h"

int main()
{
    // **** SINGLE POINTER **** //

    // Make the smart pointer and allocate an (empty) object to it
    // 'make_****' is usually preferred; only needs 1 memory allocation
    auto pos = std::make_unique<Position>(1, 2);
    
    std::cout << "Position x-value: "<< pos->getX() << std::endl;
    std::cout << "Position y-value: "<< pos->getY() << std::endl;

    // **** VECTOR OF POINTERS **** //
    std::vector<std::shared_ptr<Position>> positions;
    for(int i=1; i<=10; i++)
    {
        positions.push_back(std::make_shared<Position>(i, i));
        std::cout << "At " << i << ": (" << positions.at(i-1)->getX() << ", " << positions.at(i-1)->getY() 
          << ")" << std::endl;
    }
}