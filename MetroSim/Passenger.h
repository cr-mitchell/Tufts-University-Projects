/*
 *  Passenger.h
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * This is a struct declaration for a Passenger. A passanger can be 
 * initalized with just declaring a new Passenger or declaring a new
 * Passenger with a new id, arrival station and departure station in 
 * in the declaration
 *
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
