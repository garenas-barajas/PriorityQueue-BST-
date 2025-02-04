#include <iostream>

#include "prqueue.h"

using namespace std;

int main() {
    // Create the original BST
    prqueue<int> original;
    original.enqueue(0, 6);
    original.enqueue(1, 1);
    original.enqueue(2, 15);
    original.enqueue(3, 2);
    original.enqueue(4, 4);
    original.enqueue(5, 10);
    original.enqueue(6, 20);

// Enqueue: priority=6	value=0
// Enqueue: priority=1	value=1
// Enqueue: priority=15	value=2
// Enqueue: priority=2	value=3
// Enqueue: priority=4	value=4
// Enqueue: priority=10	value=5
// Enqueue: priority=20	value=6

    // Print both BSTs
    cout << "Original BST:" << endl;
    cout << original.as_string() << endl;

    int value;
    int priority;

    original.begin();

    while(original.next(value, priority)){
        cout << "Value: " << value << " Priority: " << priority << endl;
    }

    return 0;
}

//g++ -O2 -Wall -I. -g -std=c++2a prqueue_main.cpp prqueue.h -o prqueue_main
//./prqueue_main

