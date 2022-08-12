// Charles Mitchell, 01-31-2022, make_change.cpp 

#include <iostream>

using namespace std;

int main() 
{  
    // initializes 5 integer variables
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    int change;
    
    // asks user to to give an integer for how many change they need
    cout << "Amount of change in cents: ";
    cin >> change;
    
    /* determine how much of each currency is needed if change is or is over 
    25 cents then subtracts the amount of each currenncy that is calculated 
    until the change variable is at 0 */
    if (change % 25 >= 0) {
        
        quarters = change / 25;
        change = change - (quarters * 25);
        
        dimes = change / 10;
        change = change - (dimes * 10);
        
        nickels = change / 5;
        change = change - (nickels * 5);
        
        pennies = change;
        change = change - pennies;
    
    // same thing as above conitional but if the change is 10 cents or less    
    } else if (change % 10 >= 0){
        
        dimes = change / 10;
        change = change - (dimes * 10);
        
        nickels = change / 5;
        change = change - (nickels * 5);
        
        pennies = change;
        change = change - pennies;
    
    // same thing as above conitional but if the change is 5 cents or less    
    } else if (change % 5 >= 0) {
        
        nickels = change / 5;
        change = change - (nickels * 5);
        
        pennies = change;
        change = change - pennies;
    
    // same thing as above conitional but if the change is 1 cents or less    
    } else if (change % 1 >= 0) {
        
        pennies = change;
        change = change - pennies;
        
    }
    
    // prints out the calculated total of each variable
    cout << quarters << " quarters, " << dimes << " dimes, " << nickels;
    cout << " nickels, " << pennies << " pennies" << endl;
    
    return 0;
}
