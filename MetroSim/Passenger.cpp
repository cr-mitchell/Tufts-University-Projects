/*
 *  Passenger.cpp
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * Function definitions for the Passenger strcut. The only function is a 
 * printing function
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name: print
 * purpose:  prints all of the Passengers info
 * arguments: operator to input cout
 * returns: none
 * effects: prints Passenger;
 */
void Passenger::print(std::ostream &output)
{       
        //output is replaced by cout in a function call
        output << "[" << id << ", " << from << "->" << to << "]";
}
