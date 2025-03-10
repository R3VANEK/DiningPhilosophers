#include <iostream>
#include <thread>
#include <chrono>
#include "Philosopher.h"
#include "Waiter.h"

using namespace std;

const int Philosopher::MAX_HUNGER = 10;
Waiter* Philosopher::waiter = nullptr;

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
    while (true) {
        this->state = THINKING;
        this->starve();

        // Philosopher tries to pick up forks using the waiter
        if (Philosopher::waiter->canPickUpForks(forkLeft, forkRight)) {
            this->eat();
            Philosopher::waiter->releaseForks(forkLeft, forkRight);
        }

        this_thread::sleep_for(chrono::milliseconds(rand() % 2500 + 1));  // Random thinking time
    }
}

void Philosopher::eat() {
    this->state = EATING;
    cout << "id: " << this->id << " is eating..." << endl;
}

void Philosopher::starve() {
    this->hungerLevel++;

    if (this->hungerLevel > Philosopher::MAX_HUNGER)
        this->state = DEAD;
    else if (this->hungerLevel > Philosopher::MAX_HUNGER / 2)
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

pair<int, int> Philosopher::getForks() {
    return { this->forkLeft, this->forkRight };
}

string Philosopher::serialize() {
    return "id: " + to_string(id) + "    | state: " + this->convertState() + "    | hunger: " + to_string(hungerLevel) + "/" + to_string(Philosopher::MAX_HUNGER) + "    |";
}
