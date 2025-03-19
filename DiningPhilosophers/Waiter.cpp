#include "Waiter.h"
#include <condition_variable>

Waiter::Waiter(int philosopherCount) {

    // Initialize one mutex per philosopher (fork)
    this->forks = vector<mutex>(philosopherCount);  
}

void Waiter::pickUpForks(int leftFork, int rightFork) {
    unique_lock<mutex> lock(waiterMutex);

    condition.wait(lock, [&]() {
        return forks[leftFork].try_lock() && forks[rightFork].try_lock();
    });

}

void Waiter::releaseForks(int leftFork, int rightFork) {
    unique_lock<mutex> lock(waiterMutex);

    // Release the locks on both forks
    forks.at(leftFork).unlock();
    forks.at(rightFork).unlock();

    this->condition.notify_all();
}
