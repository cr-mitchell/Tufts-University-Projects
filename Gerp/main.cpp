/*
 *  main.cpp
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 * Description: This is the main function of the program that initializes 
 * everything. The function takes in the arguments entered on the command line 
 * and stores them in strings to determine input directory and output file and 
 * then calls an instance of gerp.
 *
 */

#include "process.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Usage: ./gerp inputDirectory outputFile" << endl;
        return 1;
    }
    
    string directory = argv[1];
    string outputfile = argv[2];

    gerp go;
    go.start(directory, outputfile);

    return 0;
}