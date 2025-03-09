#include <iostream>
#include <string>
#include <vector>

#include "Philosopher.h"
using namespace std;


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

    for (int i = 0; i < philosophersCount; i++) {
        philosophers.push_back(Philosopher(i, i + 1, i + 2));
    }

}
