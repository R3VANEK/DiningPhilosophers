#include "Waiter.h"

Waiter::Waiter(int philosopherCount) {
    this->forks = vector<mutex>(philosopherCount);  // Initialize one mutex per philosopher (fork)
}

bool Waiter::canPickUpForks(int leftFork, int rightFork) {
    lock_guard<mutex> lock(waiterMutex);

    // Try to lock both forks
    return forks.at(leftFork).try_lock() && forks.at(rightFork).try_lock();
}

void Waiter::releaseForks(int leftFork, int rightFork) {
    lock_guard<mutex> lock(waiterMutex);

    // Release the locks on both forks
    forks.at(leftFork).unlock();
    forks.at(rightFork).unlock();
}
