// Charles Mitchell, 01-31-2022, Lab LG 

#include <iostream>

using namespace std;

int main()
{ 
    //initializes 8 float variables
    float num1;
    float num2;
    float num3;
    float num4;
    float num5;
    float num6;
    float num7;
    float num8;
    
    
    //ask the user to input a float variable 8 seperate times
    cout << "Enter a floating point number: ";
    cin >> num1; 
    cout << "Enter a floating point number: ";
    cin >> num2;
    cout << "Enter a floating point number: ";
    cin >> num3;
    cout << "Enter a floating point number: ";
    cin >> num4;
    cout << "Enter a floating point number: ";
    cin >> num5;
    cout << "Enter a floating point number: ";
    cin >> num6;
    cout << "Enter a floating point number: ";
    cin >> num7;
    cout << "Enter a floating point number: ";
    cin >> num8;
    
    /* adds the floating point values and adds them and stores them into 
    a new float variable named sum. Then prints out the sum to user */
    float sum = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8;
    cout << "The sum is: " << sum << endl;
    
    return 0;

}