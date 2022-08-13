// bicycles.cpp
// by: Charles Mitchell
// date: 02-082022

/* In this homework assignment, we were asked to create a program that
calculates how many bikes can be made given the amount of wheels, links, and
frames provided by the user. 50 links, 2 wheels, and 1 frame make 1 bike. 
If there are leftover parts, then returns them to the user */

#include <iostream>

using namespace std;

int numwheels(int wheels);
int numlinks(int links);
string plural(string word, int num);
int main ()
{
    // initizalize 4 integer variables 
    int wheels, frames, links, bikes;
    
    // asks the user to enter how many wheels, frames, and links they have
    cout << "Enter the number of wheels: ";
    cin >> wheels;
    
    cout << "Enter the number of frames: ";
    cin >> frames;
    
    cout << "Enter the number of links: ";
    cin >> links;
    
    //stores the return values from our two functions into 2 integers
    int wheels_used = numwheels(wheels);
    int links_used = numlinks(links);
    
    /* 3 conditionals that determines how many bikes their our based on 
    how many parts we have that could make the maximum number of complete
    bikes */
    if (wheels_used <= frames and wheels_used <= links_used) {
        bikes = wheels_used;
    } else if (frames <= wheels_used and frames <= links_used) {
        bikes = frames;
    } else if (links_used <= wheels_used and links_used <= frames) {
        bikes = links_used;
    }
    
    /* calculates how much of each part is left over from how many bikes 
    we made */
    int leftoverwheels = wheels - (bikes * 2);
    int leftoverframes = frames - bikes;
    int leftoverlinks = links - (bikes * 50);
    
    /* prints how many bikes were made and how many parts were left over. every 
    part is given to the plural function to check if the word needs to be 
    plural */
    cout << "You can make " << bikes << " " << plural("bike", bikes)
    << ". There are " << leftoverwheels << plural(" wheel", leftoverwheels) 
    << ", " << leftoverframes << " " << plural("frame", leftoverframes) << ", " 
    << leftoverlinks << plural(" link", leftoverlinks) << " leftover." << endl;
    
    return 0;
}

// returns how many bikes we can make with just wheels taken into account
int numwheels(int wheels) 
{
    int bikewheels = wheels / 2;
    return bikewheels;
}

// returns how many bikes we can make with just links taken into account
int numlinks(int links)
{
    int bikelinks = links / 50;
    return bikelinks;
}

// returns a string plural or not plural based on a conditional
string plural(string word, int num)
{
    if (num > 1 or num == 0){
        return word + "s";
    } else {
        return word;
    }
}
