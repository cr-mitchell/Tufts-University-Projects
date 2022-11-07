/*  MetroSim.h
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * This is a class declaration for a MetroSim. A struct of Stations is defined
 * and then a vector of the Stations are made in the class definition. A vector
 * of PassengerQueues is declared as the train and all the functions that
 * manipulate both vectors are delcared in this class
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <vector>

using namespace std;


struct Stations {
    int id;
    string name;
    PassengerQueue queue;
};

class MetroSim
{
public:
    void commandloop(int size, ostream &output);
    void commandloop_comfile(int size, istream &input, ostream &output);
    vector<PassengerQueue> train;
    vector<Stations> stations;

private:
    void print(int index);
    void addPassenger(Passenger add);
    void addPassengerTrain(Passenger add);
    void removePassenger(int id);
    void removePassengerTrain(int id);
    void getOnTrain(int id);
    void getOffTrain(int id, ostream &output);
    void outputWrite(Passenger write, string station, ostream &outstream);
};

#endif
