// digits.cpp
//      purpose: report the number of digits in an integer
//        shows: use of output, input, conditional statements
//         note: has bugs, needs work
//
//  modified by: Charles Mitchell
//         date: 01-31-2022
//

#include <iostream>

using namespace std;

int main()
{
        // initializes an integer variable
        int input;
        
        // asks user to inter integer of choice
        cout << "Enter a number: ";
        cin  >> input;

        /* a string of conditional statements that determines how many 
        digits are in the intger the user inputed */
        if (input >= 100) {
                cout << "input has three or more digits" << endl;
        } else if (input >= 10) {
                cout << "input has two digits" << endl;
        } else if (input <= -100) {
                cout << "input has three or more digits" << endl;
        } else if (input <= -10) {
                cout << "input has two digits" << endl;
        } else if (input >= -9) {
                cout << "input has one digit" << endl;
        }
        
        // a conitional thhat determines if the user's input is negative
        if (input <= -1) {
                cout << "and input is negative" << endl;    
        }

        return 0;
}
