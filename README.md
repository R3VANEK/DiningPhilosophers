# Dining Philosopher dilema in C++
[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/cc-by.svg)](https://forthebadge.com)

## Table of Contents
* [Whats the problem?](#Whats-the-problem)
* [How to solve it](#How-to-solve-it)
* [Computer science analogy](#Computer-science-analogy)
* [How to run program](#How-to-run-program)
* [License](#License)

## Whats the problem?
![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/81/Dining_philosophers_diagram.jpg/1024px-Dining_philosophers_diagram.jpg)


Imagine given scenario. At round table sit 5 hungry philosophers with only 4 forks. They either think or eat and want to eat very often. To do this, they need to pick up 2 forks that are in front of them. This means, that only 4 philosophers can eat at the same time, becouse the fifth one will have only 1 fork and must wait for the others to finish eating to pick second fork

This sounds rather easy to solve in real life, right? Just let them communicate and out of courtesy eat fairly and give forks to the most hungry ones first. But to complicate things, we assume that each philosopher is gready and selfish. They don't care about the others, meaning 2 scenarios:

- Survival of the fittest: If some philosophers are fast enought, they will always pick their forks and other, slower ones will die of starvation

- Hey thats mine!: 2 or more philosophers may be equally fast and try to pick their forks at the exact same moment, meaning no one will get them

## How to solve it
There are several solutions to handle such selfish philosophers. In this repo, I used a waiter approach.

We introduce additional person to the table, a waiter. He manages all the forks. Now, if philosopher wants to eat, he must ask waiter for his forks. The waiter checks if the forks are not used and handles them immediately or ask philosopher to wait until they are free, and handles them as soon as others stop using them. This covers 2 problematic scenarios given earlier:

- Survival of the fittest: No matter the speed of philosopher, everyone will get to eat. If the forks are occupied, the waiter will handle them to the asker as soon as possible


- Hey thats mine!: Becouse philosopher asks for forks, there is no scenario that 2 or more persons grabs them at the same moment

## Computer science analogy
This problem was given by Edsger Dijkstra to visualise problems with multi-threading applications and accesing shared resources. Each philosopher is an independent thread and forks are shared resources. The problems are still the same, but under another names:

- Race conditions/starvation (Survival of the fittest): Each thread tries to access the same resource, but some are slightly faster than others meaning we have absolutely no control which thread will access it and we cannot guarantee that for another cycle the same thread will not win the race. Some slow threads may never access shared resources

- Deadlock (Hey thats mine!): Each thread needs two shared resources. There might be a situation that thread A sucessfully grabs (lock) one of it, thread B locks the second one. Now thread A waits for thread B to unlock the second resource and thread B waits for thread A to release the first one. No thread can continue and wait infinitely

To handle it, we introduce a waiter. If thread wants to acquire shared resources, it asks waiter for it. Waiter creates critical section of grabbing two resources, meaning he locks other threads for trying to access it, locks both resources and then after some time releases them. This mitigates deadlocks, becouse the waiter with a help of mutex lock grabs 2 resources at the same time and with sleeping the thread on failure to lock them and waking thread up if they will be available solving starvation/race conditions


## How to run program
Open .exe found in this repo or clone the project and open it in Visual Studio. Alternatively, you can copy all the `.cpp` and `.h` files found under `./DiningPhilosopher` folder and compile them in console using for example g++


## Licence
[CC BY](https://creativecommons.org/licenses/by/4.0/legalcode)