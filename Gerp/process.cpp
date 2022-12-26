/*
 *  process.cpp
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: Function defintions for the gerp class. On running, all file
 *  data is read into our hash table and vector of structs with file paths and
 *  names. Then the query function is called to started search for words and 
 *  printing its results into a file of choice
 *
 */

#include "process.h"

using namespace std;


/* name: start
 * purpose: calls helper functions to populate a vector of structs with file
 * names and file paths and to populate our hash table (our vectors of list
 * of struct instances contating the word, a lowercase case of the word, and
 * the line, line number, and path the word occurs on)
 * arguments: takes in users directory of choice and an string containing an 
 * inital outputfile to print results to. 
 * returns: none
 * effects: populates all of our data structs
 */
void gerp::start(string directory, string outputfile)
{  
    int index = 0;

    //throws error if FSTree was not able to be built
    try {
        goPaths(directory);
    } catch (...) {
        cerr << "Could not build index, exiting." << endl;
        return;
    }

    goValues();
    query(cin, outputfile, index);
    return;
}


/* name: goPaths
 * purpose: creates an instance of the FSTreeTraversal class and populates our
 * vector of struct instances containing a file name and its path
 * arguments: takes in users directory of choice
 * returns: none
 * effects: populates our vector of struct instances
 */
void gerp::goPaths(string directory)
{
    FSTreeTraversal getPaths;
    getPaths.createTree(directory, paths);
}


/* name: goValues
 * purpose: creates in instance of the Values class and opens up everyfile in 
 * from the users inputed directory and populates our hash table
 * arguments: none
 * returns: none
 * effects: populates our vector of list of struct instances (hash table)
 */
void gerp::goValues()
{
    //pushes 1000000 empty list to our hashtable
    list<valueMoments> temp;
    int all_value_size = 15000000;
    for (int i = 0; i < all_value_size; i++) {
        values.push_back(temp);
    }

    ifstream instream;
    unsigned long size = paths.size();
    Values getValues;
    int count = 1;

    //loop to open every file
    for (unsigned long i = 0; i < size; i++) {
        string file = paths.at(i).file_name;
        string path = paths.at(i).file_path;

        instream.open(path);
        if (not instream.is_open()) {
            throw runtime_error("Unable to open file " + file);
        }

        getValues.openFile(instream, path, values, count);

        instream.close();
    }
} 


/* name: query
 * purpose: starts the word search query which searches through our hash table
 * for a word of choice (the specific instance of the word or all cases of the
 * word and writes them to an outputfile)
 * arguments: a instream variable used for the user to cin, a outputfile, an 
 * interger to keep track of query calls
 * returns: none
 * effects: writes results of query search to an outputfile
 */
void gerp::query(istream &input, string file, int &index)
{
    ofstream output;
    output.open(file);

    //opens initial outputfile
    if (not output.is_open()) {
        throw runtime_error("Unable to open file " + file);
        return;  
    }

    if (index == 0) {
        cout << "Query? ";
    }
    string wordSearch;

    //starts query
    while(input >> wordSearch) {
        //quits program
        if (wordSearch == "@q" or  wordSearch == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            output.close();
            return;
        }

        cout  << "Query? ";

        //search for all instances of a word and writes results to outputfile
        if (wordSearch == "@i" or wordSearch == "@insensitive") 
        {
            input >> wordSearch;
            string process = stripNonAlphaNum(wordSearch);
            set<string> print = insensitive(process);

            for (set<string>::iterator it = print.begin(); it != print.end(); 
                it++) {
                output << *it;
            }
        }
        //closes current outputfile and opens a new one of users choice
        else if (wordSearch == "@f") {
            input >> wordSearch;
            
            output.close();
            index++;
            output.open(wordSearch);

            if (not output.is_open()) {
                throw runtime_error("Unable to open file " + wordSearch);
                return;  
            }
        }
        //searchs for a specific word and write results to outputfile
        else {
            string process = stripNonAlphaNum(wordSearch);
            set<string> print = AnyString(process);

            for (set<string>::iterator it = print.begin(); it != print.end(); 
                it++) {
                output << *it;
            }
        }    
    }
}


/* name: Anystring
 * purpose: searches the hash table for a specific instances of a word and
 * stores its line information into a set of strings
 * arguments: a word to search for
 * returns: a set of strings (where the word occurs)
 * effects: none
 */
set<string> gerp::AnyString(string word)
{
    //gets hash index for word to search
    unsigned int index2 = hash<string>{}(word) % values.size();
    string output = "";
    set<string> get;
    list<valueMoments>::iterator it;

    //prints all line information for instances of word to search
    for (it = values[index2].begin(); it != values[index2].end(); it++) {

        //checks to see if the word in that index is actually the input word
        if (it->word == word) { 
            output = it->line + "\n";
            get.insert(output);
        }
    }

    //checks to see if anything was found
    if (get.size() == 0) {
        output = word + " Not Found. Try with @insensitive or @i.\n";
        get.insert(output);
    }

    return get;
}


/* name: insensitive
 * purpose: searches the hash table for a all instances of a word and
 * stores its line information into a set of strings
 * arguments: a word to search for
 * returns: a set of strings (where the word occurs)
 * effects: none
 */
set<string> gerp::insensitive(string word)
{
    string search = "";
    string output = "";
    set<string> get;
    
    //lowercases the word to search
    for (size_t a = 0; a < word.size(); a++) {
        search.push_back(tolower(word[a]));
    }

    for (unsigned long i = 0; i < values.size(); i++) {

        /* the checks for the lowercase word at the beginning of seach list in 
        the has table */
        string check = values.at(i).front().lower;
        if (check == search) {
            list<valueMoments>::iterator it;
            for (it = values[i].begin(); it != values[i].end(); it++) {
                if (it->lower == search) { 
                    output = it->line + "\n";
                    get.insert(output);
                }
            }
        } 
    }

    //checks to see if anything was found
    if (get.size() == 0) {
        output = word + " Not Found.\n";
        get.insert(output);
    }
    return get;
}


