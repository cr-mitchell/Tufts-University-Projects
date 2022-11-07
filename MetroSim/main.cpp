/*  main.cpp
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * This is the main function of the program that initializes everything. The
 * files are read into main and MetroSim is called here to start the 
 * simulation. The station names are also stored in the vector of Stations in
 * main as well.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[])
{
        if (argc < 3 or argc > 4) {
                cerr << "Usage: ./MetroSim stationsFile outputFile"
                     << " [commandsFile]" << endl;

                return 1;
        }

        ifstream instream;
        ofstream outstream;
        string filename = argv[1];
        string printoutput = argv[2];
        int count_id = 0;
        string line;

        instream.open(filename);
        outstream.open(printoutput);

        if (not instream.is_open()) {
                cerr << "Error: could not open file " << filename << endl;
                return 1;
        }

        if (not outstream.is_open()) {
                cerr << "Error: could not open file " << printoutput << endl;
                return 1;
        }

        //initalizes the simulation, but not the command loop just yet
        MetroSim metroGo;

        /*reads the station names from the file and stores them in the vector
        of Stations structs*/
        while (not getline(instream, line).fail()) {
                Stations read;
                read.name = line;
                read.id = count_id;

                count_id++;
                metroGo.stations.push_back(read);
        }
        
        instream.close();

        /*use of an iterator to store the exact same number of PassengerQueues
        in the train, but they are empty*/
        vector<Stations>::iterator it = metroGo.stations.begin();

        while (it != metroGo.stations.end()) {
                Stations temp = *it;
                PassengerQueue initalize;

                metroGo.train.push_back(initalize);

                it++;
        }

        //this is how many stations were read in from the stations file
        int size = metroGo.stations.size(); 

        /*if a command.txt file is passed in, check all conditions for the new
        file and then commence the metrosim command loop for file commands*/
        /*else if a command.txt file is not passed in, commence the metrosim 
        command loop for cin commands*/
        if (argc == 4) {
                ifstream instream2;
                string filename2 = argv[3];
                instream2.open(filename2);

                if (not instream2.is_open()) {
                cerr << "Error: could not open file " << filename2 << endl;
                return 1;
                }

                metroGo.commandloop_comfile(size, instream2, outstream);
                instream2.close();

        } else if (argc == 3) {
                metroGo.commandloop(size, outstream);
        }

        outstream.close();
        return 0;
}
