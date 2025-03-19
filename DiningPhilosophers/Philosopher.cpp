#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <random>   
#include <sstream>
#include "Philosopher.h"
#include "Waiter.h"

using namespace std;

const int Philosopher::MAX_HUNGER = 10;
Waiter* Philosopher::waiter = nullptr;
thread_local mt19937 Philosopher::rng(random_device{}());

Philosopher::Philosopher(int id, int forkLeft, int forkRight) {
    this->id = id;
    this->forkLeft = forkLeft;
    this->forkRight = forkRight;
    this->state = THINKING;
    this->hungerLevel = 0;
    this->worker = thread(&Philosopher::think, this);
}
    
void Philosopher::setWaiter(Waiter* newWaiter) {
    Philosopher::waiter = newWaiter;
}

void Philosopher::think() {
    uniform_int_distribution<int> sleepTime(1, 5000);

    while (true) {
        this->state = THINKING;
        this->starve();

        // Philosopher tries to pick up forks using the waiter
        if (this->state == STARVING) {
            if (Philosopher::waiter->pickUpForks(forkLeft, forkRight)) {
                this->eat();
                Philosopher::waiter->releaseForks(forkLeft, forkRight);
            }
        }
       
        // Random thinking time
        this_thread::sleep_for(chrono::milliseconds(sleepTime(this->rng)));
    }
}

void Philosopher::eat() {
    this->state = EATING;
    this->hungerLevel = 0;
}

void Philosopher::starve() {
    this->hungerLevel++;

    if (this->hungerLevel > Philosopher::MAX_HUNGER)
        this->state = DEAD;
    else if (this->hungerLevel >= Philosopher::MAX_HUNGER / 2)
        this->state = STARVING;

    if (this->state == DEAD)
        throw exception("Oh no, philosopher is dead!");
}

void Philosopher::join() {
    if (this->worker.joinable())
        this->worker.join();
}

string Philosopher::convertState() {
    switch (this->state) {
        case EATING: return "EATING";
        case THINKING: return "THINKING";
        case STARVING: return "STARVING";
        case DEAD: return "DEAD";
        default: return "UNKNOWN";
    }
}


string Philosopher::serialize() {
    ostringstream output;

    output << "id: " << setw(2) << id
        << " | state: " << setw(9) << left << this->convertState()
        << " | hunger: " << setw(2) << hungerLevel << "/" << Philosopher::MAX_HUNGER
        << " |";

    return output.str();
}
