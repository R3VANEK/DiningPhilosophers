#include <iostream>
#include <thread>
#include <functional>

#include "Philosopher.h"


using namespace std;

void Philosopher::think() {

	while (true) {
		this->state = THINKING;
		cout << endl << "id: " << this->id << " is thinking...";
		this_thread::sleep_for(500ms);
	}
	
}

Philosopher::Philosopher(int id, int forkLeft, int forkRight) {
	this->forkLeft = forkLeft;
	this->forkRight = forkRight;
	this->state = THINKING;
	this->id = id;

	this->worker = thread(&Philosopher::think, this);
}

void Philosopher::eat() {
	this->state = EATING;
	cout << "id: " << this->id << " is eating...";
}

