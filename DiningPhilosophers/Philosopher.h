#pragma once
#include <thread>
#include <string>
#include "Waiter.h"

using namespace std;

class Philosopher {

	static Waiter* waiter;
	const static int MAX_HUNGER;

	enum STATE {
		EATING,
		THINKING,
		STARVING,
		DEAD
	};

	int id;
	int forkLeft;
	int forkRight;
	int hungerLevel;
	STATE state;
	thread worker;

public:

	// maybe in the future make silent death as an option?
	Philosopher(int id, int forkLeft, int forkRight);
	void eat();
	void think();
	void join();
	pair<int, int> getForks();
	string serialize();

	static void setWaiter(Waiter* newWaiter);

	bool operator < (const Philosopher& other) const {
		return hungerLevel < other.hungerLevel;
	}

private:
	string convertState();
	void starve();
};