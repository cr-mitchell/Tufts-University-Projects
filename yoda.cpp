// Charles Mitchell, 01-31-2022, Lab LG 

#include <iostream>

using namespace std;

int main()
{
    // initializes four string variables
    string first_word, second_word, third_word, fourth_word;
    
    // ask user to input 4 words
    cout << "Type in four words: ";
    cin >> first_word >> second_word >> third_word >> fourth_word;

    // print the words out in reverse order
    cout << fourth_word << " " << third_word << " ";
    cout << second_word << " " << first_word << " " << endl;
    
    return 0;
    
}