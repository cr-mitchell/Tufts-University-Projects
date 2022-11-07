/*
 *  RPNCalc.h
 *  Charles Mitchell
 *  10/26/2022
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 * This is a class declaration for RPNCalc. Only the constructor and run 
 * functions are public while the all other functions and DatumStack 
 * and variable declarations are private to prevent user messing with 
 * computations in the calculator
 *
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include <vector>
#include "DatumStack.h"

using namespace std;

class RPNCalc {
public:
    RPNCalc();
    void run();

private:
    string com;
    DatumStack stack;
    void runImplement(istream &input);
    void createNum(string input);
    void createBool(string input);
    void createRString(istream &input);

    // function below is for when user enters "not"
    void swapBool();
    void print();
    void clear();
    void drop();
    void duplicate();
    void swapTop();
    void operCompute(string operate);
    void operCompare(string operate);
    void execute(string operate);
    void file();
    void ifCommand();
    bool got_int(string s, int *resultp);
    std::string parseRString(std::istream &input);
};

#endif