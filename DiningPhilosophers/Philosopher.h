#pragma once
#include <thread>
#include <string>
#include <random>
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

	Philosopher(int id, int forkLeft, int forkRight);
	void join();
	string serialize();

	static void setWaiter(Waiter* newWaiter);

private:
	static thread_local mt19937 rng;
	string convertState();
	void starve();
	void think();
	void eat();
};