// pattern.cpp
// by: Charles Mitchell
// date: 02-15-2022
/* purpose: Takes a user's input of two words and a number of choice a prints 
the words on the inputed amount of times alternating which word starts
first. Achieved via a recursive function */

#include <iostream>
using namespace std;

void output_pattern(string s1, string s2, int n);
int main()
{
    // initalize two string variables and one integer variable
    string one, two;
    int repeat;
    
    // prompts user to enter in two words and an integer of their choice
    cin >> one >> two >> repeat;
    
    // calls the function 
    output_pattern(one, two, repeat);
    
    return 0;
}

/* this is a recursive function that returns nothing and prints the the two
words the user inputed, alternating one after the other, and swithcing which
one begins on each new line. the number of lines is the integer the user
gave */
void output_pattern(string s1, string s2, int n)
{
    // stops if the integer is 0 or less
    if (n <= 0) {
    } else {
        cout << s1 << s2 << s1 << s2 << s1 << s2 << s1 << s2 << s1 << s2 <<
        endl;
        
        // calls itself with a decreasing parameter and swaped words
        output_pattern(s2, s1, n - 1);
    }
    
}