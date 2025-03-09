#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "Philosopher.h"
using namespace std;

void clearScreen(int lines) {
    cout << "\033[" << lines << "A";
    cout << "\033[J";
}

int main(int argc, char* argv[])
{
    int philosophersCount = NULL;

    try {
        if (argc == 2)
            philosophersCount = stoi(argv[1]);
        else {
            cout << "Please specify the number of philosophers: ";
            cin >> philosophersCount;
        }
    }
    catch (const exception& e) {
        cout << endl << "Something went wrong with passing philosopher number, please try again";
        return 1;
    }
   

    vector<Philosopher> philosophers;
    philosophers.reserve(philosophersCount);

    // initializing the philosophers and making sure
    // that no copying and slicing to the objects disturb their threads
    for (int i = 0; i < philosophersCount; i++)
        philosophers.emplace_back(i, i + 1, i + 2);
    

    // main loop for printing out all of the philosopher info
    while (true) {
        for (int i = 0; i < philosophersCount; i++)
            cout << philosophers[i].serialize() << endl;

        this_thread::sleep_for(2s);
        clearScreen(philosophersCount);
    }


    // wait until all threads are finished before closing the app
    // won't happen as philosopher's threads are infinite but to prevent errors popping out
    for (int i = 0; i < philosophersCount; i++)
        philosophers[i].join();

    return 0;

}
