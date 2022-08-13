// flights.cpp
// by: Charles Mitchell
// date: 02-08-2022

/* In this homework assignment, we were asked to create a program that takes
one flight and a connecting flight's exact hour and minute they take off and 
land and use this information give the user their layover time and total time 
travled in hours and in minutes. We also had to keep in mind for over night 
flights in which this program handles. This program does not handle
time zones */ 

#include <iostream>
using namespace std; 

void layover(int flight2hr_take, int flight2min_take, int flight1hr_land,
     int flight1min_land);
void total(int flight1hr_take, int flight1min_take, int flight2hr_land,
     int flight2min_land);
int main()
{
    
    /* initizalize 8 integer variables. 2 for the time flight one takes off, 2 
    for the time flight one lands, 2 for when flight two takes off, and 2 for 
    when flight 2 lands */
    int flight1hr_take, flight1min_take, flight1hr_land, flight1min_land;
    int flight2hr_take, flight2min_take, flight2hr_land, flight2min_land;
   
    //ask user to enter times flight one takes off and lands
    cout << "Flight 1: ";
    cin >> flight1hr_take;
    cin >> flight1min_take;
    cin >> flight1hr_land;
    cin >> flight1min_land;
   
    //ask user to enter times flight two takes off and lands
    cout << "Flight 2: ";
    cin >> flight2hr_take;
    cin >> flight2min_take;
    cin >> flight2hr_land;
    cin >> flight2min_land;
    
    //calls are two void functions that are below the main function 
    layover(flight2hr_take, flight2min_take, flight1hr_land, flight1min_land);
    total(flight1hr_take, flight1min_take, flight2hr_land, flight2min_land);
   
    return 0;
}

//this function calculates the layover time from flight 1 to flight 2
void layover(int flight2hr_take, int flight2min_take, int flight1hr_land,
     int flight1min_land)
{   
    /* initizalize 5 integer variables. totalflight2 and totalflight1 converts
    the time flight 1 landed and the time flight 2 took off into minutes */
    int layoverhr, layovermin, leftoverlayover_min;
    int totalflight2 = (flight2hr_take * 60) + flight2min_take;
    int totalflight1 = (flight1hr_land * 60) + flight1min_land;
   
    /* a conditional statement that checks if the time that flight 1 landed
    is greater than the time flight 2 took off (an overnight layover). If this 
    is the case, then 1440 min (24 hours) is added to the layovermin variable 
    to capture that there is in fact a overnight layover */
    if (totalflight1 > totalflight2) {
        layovermin = 1440 + totalflight2 - totalflight1;
    } else {
        layovermin = totalflight2 - totalflight1;
    }
   
    /* converts the calculated layovermin into hours and then takes the 
    remainder of the minutes and stores it in a variable */
    layoverhr = (layovermin / 60);
    leftoverlayover_min = layovermin % 60;
   
    // prints out the layover time 
    cout << "Layover: " << layoverhr << " hr " << leftoverlayover_min;
    cout << " min" << endl;
       
}

void total(int flight1hr_take, int flight1min_take, int flight2hr_land,
     int flight2min_land)
{
    /* initizalize 5 integer variables. totalflight2 and totalflight1 converts
    the time flight 1 landed and the time flight 2 landed into minutes */   
    int totalmin, totalhr, leftovertotal_min;
    int totalflight1 = (flight1hr_take * 60) + flight1min_take;
    int totalflight2 = (flight2hr_land * 60) + flight2min_land;
   
    /* a conditional statement that checks if the time that flight 1 landed
    is greater than the time flight 2 landed (an overnight flight). If this 
    is the case, then 1440 min (24 hours) is added to the totalmin variable 
    to capture that there is in fact a overnight flight */
    if (totalflight2 < totalflight1){
        totalmin = 1440 + (totalflight2 - totalflight1);
    } else {
        totalmin = totalflight2 - totalflight1;
    }
    
    /* converts the calculated layovermin into hours and then takes the 
    remainder of the minutes and stores it in a variable */
    totalhr = (totalmin / 60);
    leftovertotal_min = totalmin % 60;
    
    // prints out the total time 
    cout << "Total: " << totalhr << " hr " << leftovertotal_min;
    cout << " min" << endl; 
       
}

