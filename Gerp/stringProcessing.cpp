/*
 *  stringProcessing.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: Function defintion for stripNonAlphaNum. This function takes
 *  a word and checks if the inserted string has non alphanumeric characters
 *  after the last alphanumeric character and before the first alphanumeric
 *  character and strips them from the string.
 *
 */


#include <iostream>
#include <cctype>
#include <clocale>
#include "stringProcessing.h"

/*
 * name:      stripNonAlphaNum
 * purpose:   remove all leading and trailing non-alphanumeric characters 
 *            from the given string,
 * arguments: the user's word to search
 * returns:  the new word stripped of non-alphanumeric characters
 * effects:   none
 */
std::string stripNonAlphaNum(std::string input) 
{
    int size = input.size();
    int last = 0;
    int first = 0;
    string new_input = "";

    //gets the index of the last alphanumeric character
    for (int i = 0; i < size; i++) {
        if (isalnum(input[i])) {
            last = i;
        }
    } 

    //gets the index of the first alphanumeric character
    for (int j = size - 1; j >= 0; j--) {
         if (isalnum(input[j])) {
            first = j;
        }
    }

    //strips string from the first and last index from previous loops
    if (first != last) {
        for (int k = first; k <= last; k++) {
            new_input.push_back(input[k]);
        }
    }
    return new_input;
}