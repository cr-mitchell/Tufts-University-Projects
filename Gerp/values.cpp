/*
 *  values.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: Function defintions for the Values class. On running, the size
 *  of the hash table (our vector of list of struct instances) is set. The
 *  open file function is then called and reads in each line and each word
 *  from the each line and creates an instance of declared struct and inserts
 *  it into our hash table.
 *
 */


#include "values.h"
#include "stringProcessing.h"
using namespace std;


/* name: Values
 * purpose: sets the size of our hash table
 * arguments: none
 * returns: none
 * effects: sets the size of our hash table
 */
Values::Values() 
{
    all_value_size = 15000000;
}


/* name: openFile
 * purpose: adds struct instances into our hash table
 * arguments: an opened file, string containing the path of that file, and the
 * reference of our hash table (vector of list of struct instances)
 * returns: none
 * effects: populates the hash table (vector of list of struct instances)
 */
void Values::openFile(istream &input, string path, 
                      vector<list<valueMoments> > &all_values, int &count) 
{
    string line;

    //used to count line numbers
    unsigned int index = 1;
    
    // this while loop reads in every line from the opened file
    while (getline(input, line)) {
        stringstream ss(line);
        string word = "";

        /* this while loop reads in every word from the read in line using 
        stringstream */
        while (ss >> word) {
            string word2 = stripNonAlphaNum(word);

            // if (word == "wish") {
            //     cerr << word2 << endl;
            // }

            //if after stripping, all there is left is an empty string
            if (word2 != "") {
                string num = to_string(index);
                string num_line = path + ":" + num + ": " + line;
                string small = lowerCase(word2);
                insertData(all_values, word2, small, num_line);
                checkLoad(all_values, count);
                count++;
            }
        }
        index++;
    }
}


/* name: insertData
 * purpose: adds struct instances into our hash table
 * arguments: strings containg word, lowercase word, and line info, and the
 * reference of our hash table (vector of list of struct instances)
 * returns: none
 * effects: populates the hash table (vector of list of struct instances)
 */
void Values::insertData(vector<list<valueMoments> > &all_values, string word,
                    string lower, string num_line)
{
    //gets index of word in hash table
    unsigned int index = hash<string>{}(word) % all_value_size;
    
    //creates a struct instance and stores word and line info;
    valueMoments temp;
    temp.word = word;
    temp.line = num_line;
    temp.lower = lower;

    all_values.at(index).push_back(temp);
}

/* name: checkLoad
 * purpose: checks the percentage of the table thats filled
 * arguments: the reference of our hash table (vector of list of struct 
 * instances) and an integer that counts how much data is in the table
 * returns: none
 * effects: calls the resizeTable function if load is too large
 */
void Values::checkLoad(vector<list<valueMoments> > &all_values, int count)
{
    float load = float(count) / float(all_value_size);

    if (load > 0.8) {
        resizeTable(all_values);
    }
}


/* name: resizeTable
 * purpose: multiples table size by 2
 * arguments: the reference of our hash table (vector of list of struct 
 * instances)
 * returns: none
 * effects: doubles the current size of our hash table
 */
void Values::resizeTable(vector<list<valueMoments> > &all_values)
{
    all_value_size *= 2;
    const size_t curr_size = all_values.size();

    list<valueMoments> temp;

    for (int i = curr_size; i <= all_value_size; i++) {
        all_values.push_back(temp);
    }
}


/* name: lowerCase
 * purpose: lowerscases the word read in from the file
 * arguments: word read in from file
 * returns: lowercased version of word read in from the file
 * effects: none
 */
string Values::lowerCase(string word)
{
    string newLower = "";
    for (size_t i = 0; i < word.size(); i++) {
        newLower.push_back(tolower(word[i]));
    } 

    return newLower;
}

