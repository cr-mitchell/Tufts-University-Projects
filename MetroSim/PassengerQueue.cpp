/*
 *  PassengerQueue.cpp
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * Function definitions for the PassengerQueue class. There are various 
 * functions that either print the queue or manipulate the queue.
 *
 */

#include "PassengerQueue.h"
#include <iostream>
#include <list>

using namespace std;


/*
 * name: front
 * purpose:  returns to the current front of the queue
 * arguments: none
 * returns: Passenger at the front of the line
 * effects: none;
 */
Passenger PassengerQueue::front() 
{
    return passengers.front();
}


/*
 * name: dequeue
 * purpose:  removes the front Passenger in the PassengerQueue
 * arguments: none
 * returns: none
 * effects: shrinks the PassengerQueue by 1;
 */
void PassengerQueue::dequeue()
{
    passengers.pop_front();
}


/*
 * name: enqueue
 * purpose:  adds a new Passenger to the PassengerQueue
 * arguments: none
 * returns: none
 * effects: grows the PassengerQueue by 1;
 */
void PassengerQueue::enqueue(const Passenger &passenger)
{
    passengers.push_back(passenger);
}


/*
 * name: size
 * purpose: returns the current size of the PassengerQueue
 * arguments: none
 * returns: current size of queue
 * effects: none;
 */
int PassengerQueue::size()
{
    return passengers.size();
}


/*
 * name: print
 * purpose:  prints all of the Passengers info from the PassengerQueue
 * arguments: operator to input cout
 * returns: none
 * effects: prints all Passengers;
 */
void PassengerQueue::print(ostream &output)
{
    list<Passenger>::iterator it = passengers.begin();

    while (it != passengers.end()) {
        
        Passenger temp = *it;

        temp.print(output);

        it++;
    }
}

