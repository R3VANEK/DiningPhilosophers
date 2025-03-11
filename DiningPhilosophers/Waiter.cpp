#include "Waiter.h"

Waiter::Waiter(int philosopherCount) {

    // Initialize one mutex per philosopher (fork)
    this->forks = vector<mutex>(philosopherCount);  
}

bool Waiter::pickUpForks(int leftFork, int rightFork) {
    lock_guard<mutex> lock(waiterMutex);

    // try locking left fork
    if (!forks.at(leftFork).try_lock()) {
        return false;
    }


    // try the other one
    // if it fails, unlock the first one
    if (!forks.at(rightFork).try_lock()) {
        forks.at(leftFork).unlock();
        return false;
    }

    return true;

}

void Waiter::releaseForks(int leftFork, int rightFork) {
    lock_guard<mutex> lock(waiterMutex);

    // Release the locks on both forks
    forks.at(leftFork).unlock();
    forks.at(rightFork).unlock();
}
