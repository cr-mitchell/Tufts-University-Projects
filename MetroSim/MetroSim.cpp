 /*  MetroSim.cpp
 *  Charles Mitchell
 *  10/12/2022
 *
 *  CS 15 Proj 1 MetroSim
 *
 * Function defintions for the MetroSim class. All of these functions either
 * print out the current instance of the metro simulation, adds and deletes
 * passangers from the stations and train, runs the simulation until told
 * to quit, and writes to a file where a passenger exits the train
 *
 */

#include "MetroSim.h"
#include <vector>

using namespace std;

/* name: print
 * purpose: prints out the current instance of the metro simulation
 * arguments: the current position of the train
 * returns: none
 * effects: prints out any new passengers added to a station or the train and 
 * or moves the train to the next station
 */
void MetroSim::print(int index)
{
    int compare = 0;

    cout << "Passengers on the train: {";

    /*iterator to loop through each passengerqueue in the train to print every
    passenger on the train */
    vector<PassengerQueue>::iterator it = train.begin();

    while (it != train.end()) {
        PassengerQueue temp = *it;
        temp.print(cout);
        it++;
    }

    cout << "}" << endl;

    /*second iterator to loop through and where to print the TRAIN text*/
    vector<Stations>::iterator it2 = stations.begin();

    while (it2 != stations.end()) {
        Stations temp2 = *it2;

        if (compare == index) {
            cout << "TRAIN: [" << temp2.id << "]" << " " << temp2.name << " " 
             << "{";
            temp2.queue.print(cout);
            cout << "}" << endl;
        } else {
            cout << "       [" << temp2.id << "]" << " " << temp2.name << " " 
             << "{";
            temp2.queue.print(cout);
            cout << "}" << endl;
        }
        it2++;
        compare++;
    } 
} 


 /* name: addPassenger
 * purpose:  adds a passenger to a station of choice
 * arguments: Passenger struct
 * returns: none
 * effects: adds a passenger to the stations specified from the input
 */
void MetroSim::addPassenger(Passenger add) 
{
    stations.at(add.from).queue.enqueue(add);
}


/* name: removePassenger
 * purpose:  removes passenger from a station of choice
 * arguments: none
 * returns: none
 * effects: removes a passenger from the front of a specified station queue
 */
void MetroSim::removePassenger(int id)
{
    stations.at(id).queue.dequeue();
}


/* name: addPassengerTrain
 * purpose:  adds a passenger to a train cart of choice
 * arguments: Passenger struct
 * returns: none
 * effects: adds a passenger to a train cart specified from the input
 */
void MetroSim::addPassengerTrain(Passenger add)
{
    train.at(add.to).enqueue(add);
}


/* name: removePassengerTrain
 * purpose:  removes passenger from a train cart of choice
 * arguments: none
 * returns: none
 * effects: removes a passenger from the front of a specified train cart queue
*/
void MetroSim::removePassengerTrain(int id) 
{
    train.at(id).dequeue();
}
 

/* name: commandloop
 * purpose:  runs the MetroSim simulation with std::cin commands
 * arguments: number of stations and output file
 * returns: none
 * effects: runs and calls all of other functions with given commands. 
 * manipulates stations and train queues and prints new metrosim instances
*/
void MetroSim::commandloop(int size, ostream &output) 
{
    string command;
    int count_id = 1;
    int move = 0;

    while (command != "mf" or command != "m f") {
        if (move == size) {
            move = 0;
        }

        getOffTrain(move, output);
        print(move);
        cout << "Command? ";
        getline(cin, command);
        

        if (command == "mm" or command == "m m") {
            getOnTrain(move);
            move++;
        } else if (command.substr(0, 1) == "p") {

            /*cuts up the string into substrings and turns the substrings with
            numbers into real intergers to pass into a passenger struct*/
            int placement = command.substr(2).find(" ");
            string convertfrom = command.substr(2, placement + 1);
            string convertto = command.substr(placement + 2);
            int from = stoi(convertfrom);
            int to = stoi(convertto);

            Passenger add(count_id, from, to);
            addPassenger(add);
            count_id++;
        } else if (command == "mf" or command == "m f") {
            cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
            return;
        }
    }
}


/* name: commandloop_comfile
 * purpose:  runs the MetroSim simulation with file commands
 * arguments: number of stations, input file for commmands, and output file
 * returns: none
 * effects: runs and calls all of other functions with given commands. 
 * manipulates stations and train queues and prints new metrosim instances
*/
void MetroSim::commandloop_comfile(int size, istream &input, ostream &output)
{
    char command1;
    char command2 = 'o'; 
    int count_id = 1;
    int move = 0;

    while (command2 != 'f' and not input.eof()) {
        if (move == size) {
            move = 0;
        }

        getOffTrain(move, output);
        print(move);
        cout << "Command? ";
        input >> command1;
        
        if (command1 == 'm') {
            input >> command2;

            if (command2 == 'm') {
                getOnTrain(move);
                move++;
            } else if (command2 == 'f') {
                cout << "Thanks for playing MetroSim. Have a nice day!" 
                     << endl;
                return;
            }
        } else if (command1 == 'p') {
            int from;
            int to;
            input >> from >> to;

            Passenger add(count_id, from, to);
            addPassenger(add);
            count_id++; 
        }
    }
}


/* name: getOnTrain
 * purpose:  adds passengers to the train and removes them from the station
 * arguments: current station id
 * returns: none
 * effects: adds the entire passengerqueue at a station to the train cart of
 * their destination and deletes them from the station in the process
*/
void MetroSim::getOnTrain(int id)
{
    int size = stations.at(id).queue.size();

    for (int i = 0; i < size; i++) {
        Passenger add = stations.at(id).queue.front();
        addPassengerTrain(add);
        removePassenger(id);
    }
}


/* name: getOffTrain
 * purpose:  removes passengers from the train
 * arguments: current station id and output fie
 * returns: none
 * effects: removes passengerqueue from the train cart of given station id 
 * and calls the outputWrite function to print data
*/
void MetroSim::getOffTrain(int id, ostream &outstream)
{
    int size = train.at(id).size();

    for (int i = 0; i < size; i++) {
        outputWrite(train.at(id).front(), stations.at(id).name, outstream);
        removePassengerTrain(id);
    }
}


/* name: outputWrite
 * purpose:  writes data to an output.txt file
 * arguments: Passenger struct, current station name, and output file name
 * returns: none
 * effects: writes a simple sentence to an output file that states the 
 * passengers id number and the stations name they exited from
*/
void MetroSim::outputWrite(Passenger write, string station, ostream &outstream)
{
    outstream << "Passenger " << write.id << " left train at station "
           << station << endl;
}
