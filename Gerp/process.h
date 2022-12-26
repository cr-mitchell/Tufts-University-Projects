/*
 *  process.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: This is a class declaration for a gerp. This class
 *  contains two public and six private method. The start function takes in 
 *  the users input directory and name of the output file of choice and calls
 *  our private methods to populate our hash table. The query function starts
 *  the word search and outputfile writing with the help of two private 
 *  functions
 */

#ifndef GERP_H
#define GERP_H

#include "FSTreeTraversal.h"
#include "stringProcessing.h"
#include "values.h"
#include <set>
using namespace std;

class gerp {
public:
    void start(string directory, string outputfile);
    void query(istream &input, string file, int &index);

private:
    vector<FileData> paths;
    vector<list<valueMoments> > values;
    void goPaths(string directory);
    void goValues();
    set<string> AnyString(string word);
    set<string> insensitive(string word);
};





#endif