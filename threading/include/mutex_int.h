#ifndef MUTEX_INT_H_
#define MUTEX_INT_H_

#include <mutex>

class MutexInt
{
    public:
        MutexInt(int value);
        void addToInt();
        int getValue();
    private:
        int value_;
        mutable std::mutex mx_;
};

#endif