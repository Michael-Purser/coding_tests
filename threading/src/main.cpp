#include <iostream>
#include <memory>
#include <thread>

#include "../include/mutex_int.h"

// function to call in the threads:
void increaseInt(std::shared_ptr<MutexInt> m_int_instance)
{
    for(int i=0; i<1000000; ++i)
    {
        m_int_instance->addToInt();
    }
}

int main()
{
    // instance of int with mutex
    auto m_int = std::make_shared<MutexInt>(0);

    // threads that call the add to int method
    std::thread thread_1{increaseInt, m_int};
    std::thread thread_2{increaseInt, m_int};
    std::thread thread_3{increaseInt, m_int};
    std::thread thread_4{increaseInt, m_int};
    std::thread thread_5{increaseInt, m_int};

    // join the threads:
    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();
    thread_5.join();

    // print the result:
    std::cout << "Value of m_int: " << m_int->getValue() << std::endl;
}