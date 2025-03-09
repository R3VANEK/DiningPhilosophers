#include "Philosopher.h"
#include <iostream>

using namespace std;

Philosopher::Philosopher(int id, int forkLeft, int forkRight) {
	this->forkLeft = forkLeft;
	this->forkRight = forkRight;
	this->state = THINKING;
	this->id = id;
}

void Philosopher::eat() {
	this->state = EATING;
	cout << "id: " << this->id << " is eating...";
}

void Philosopher::think() {
	this->state = THINKING;
	cout << "id: " << this->id << " is thinking...";
}