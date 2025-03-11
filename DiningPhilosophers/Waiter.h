#pragma once
#include <vector>
#include <mutex>

using namespace std;

class Waiter {

    vector<mutex> forks;

public:
    Waiter(int philosopherCount); 

    bool pickUpForks(int leftFork, int rightFork);
    void releaseForks(int leftFork, int rightFork);

private:
    mutex waiterMutex;
};
