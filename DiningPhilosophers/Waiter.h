#pragma once
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

class Waiter {

    vector<mutex> forks;

public:
    Waiter(int philosopherCount); 

    void pickUpForks(int leftFork, int rightFork);
    void releaseForks(int leftFork, int rightFork);

private:
    mutex waiterMutex;
    condition_variable condition;
};
