#pragma once
#include <vector>
#include <mutex>
#include "Philosopher.h"

using namespace std;

class Waiter {

    vector<mutex> forks;  // We need one mutex per fork

public:
    Waiter(int philosopherCount);  // Constructor to initialize forks
    Waiter(const Waiter&) = delete;  // Delete copy constructor
    Waiter& operator=(const Waiter&) = delete;  // Delete copy assignment operator

    bool canPickUpForks(int leftFork, int rightFork);  // Method to check if forks can be picked up
    void releaseForks(int leftFork, int rightFork);  // Method to release forks

private:
    mutex waiterMutex;  // Mutex for synchronizing access to the waiter itself
};
