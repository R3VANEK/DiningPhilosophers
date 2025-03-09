#pragma once
#include <thread>
#include <string>

using namespace std;

class Philosopher {

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
	string serialize();

private:
	string convertState();
	void starve();
};