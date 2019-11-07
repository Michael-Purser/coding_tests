#include "../include/mutex_int.h"

MutexInt::MutexInt(int value) :
    value_{value}
{
}

void MutexInt::addToInt()
{
    std::lock_guard<std::mutex> guard{mx_};
    ++value_;
}

int MutexInt::getValue()
{
    return value_;
}