/*  main.cpp
 *  Charles Mitchell
 *  11/17/2022
 *
 *  CS 15 Proj 3 Zap
 *
 * This is the main function of the program that initializes everything. The 
 * function takes in the arguments entered on the command line and stores
 * them in strings to determine input file, output file, and the command the
 * user wants to do
 */

#include <iostream>
#include "HuffmanCoder.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        return 1;
    }

    string command = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    HuffmanCoder go;

    if (command == "zap") {
        go.encoder(input_file, output_file);
    } else if (command == "unzap") {
        go.decoder(input_file, output_file);
    } else {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        return 1;
    }

    return 0;
}