#include <iostream>
#include <thread>
#include <chrono>
#include "Philosopher.h"


using namespace std;

const int Philosopher::MAX_HUNGER = 10;




Philosopher::Philosopher(int id, int forkLeft, int forkRight) {
	this->forkLeft = forkLeft;
	this->forkRight = forkRight;
	this->state = THINKING;
	this->id = id;
	this->hungerLevel = 0;

	this->worker = thread(&Philosopher::think, this);
}


void Philosopher::think() {

	while (true) {
		this->state = THINKING;
		this->starve();
		this_thread::sleep_for(chrono::milliseconds(rand() % 2500 + 1));
	}

}


void Philosopher::eat() {
	this->state = EATING;
	cout << "id: " << this->id << " is eating...";
}

void Philosopher::starve() {
	this->hungerLevel++;

	if (this->hungerLevel > Philosopher::MAX_HUNGER)
		this->state = DEAD;
	else if (this->hungerLevel > Philosopher::MAX_HUNGER / 2)
		this->state = STARVING;


	// TODO: make option for silent death
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
		default: return "UKNOWN";
	}
}

string Philosopher::serialize() {
	return "id: " + to_string(id) + "    | state: " + this->convertState() + "    | hunger: " + to_string(hungerLevel) + "/" + to_string(Philosopher::MAX_HUNGER) + "    |";
}
