#pragma once
#include <thread>

class Philosopher {

	enum STATE {
		EATING,
		THINKING,
		STARVING
	};

	int id;
	int forkLeft;
	int forkRight;
	STATE state;
	
	std::thread worker;

public:
	Philosopher(int id, int forkLeft, int forkRight);
	void eat();
	void think();
};