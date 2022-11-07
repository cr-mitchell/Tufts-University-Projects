/*
 *  PassengerQueue.h
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * This is a class declaration for a PassengerQueue. A PassengerQueue is 
 * simply just a list(linked list) of Passengers. The list of passengers is
 * a private member of a class while there are various functions to print 
 * the queue or manipulate it
 *
 */

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <list>

using namespace std;

class PassengerQueue {
public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(ostream &output);

private:
    list<Passenger> passengers;
};

#endif