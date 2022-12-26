/*
 *  values.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: This is a class declaration for a Values class. This class
 *  contains two public and one private method and a declaration of a stuct. 
 *  The Values constructor initializes the size of our hash table (our vector
 *  of list of sruct instances). The open file function takes in an opened 
 *  file, string that contains the path of the opened path and a reference to 
 *  our vector of list of struct instances 
 *
 */

#ifndef VALUES_H
#define VALUES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
using namespace std;



struct valueMoments {
    string word;
    string line;
    string lower;
};

class Values {
public:
    Values();
    void openFile(istream &input, string path,  
                  vector<list<valueMoments> > &all_values, int &count);
    void insertData(vector<list<valueMoments> > &all_values, string word,
                    string lower, string num_line);
    void checkLoad(vector<list<valueMoments> > &all_values, int count);
    void resizeTable(vector<list<valueMoments> > &all_values);
    string lowerCase(string word);
   
private:
    int all_value_size;
};

#endif
