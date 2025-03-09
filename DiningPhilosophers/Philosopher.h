#pragma once

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
	

public:
	Philosopher(int id, int forkLeft, int forkRight);
	void eat();
	void think();
};