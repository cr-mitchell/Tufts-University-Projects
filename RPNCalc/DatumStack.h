/*
 *  DatumStack.h
 *  Charles Mitchell
 *  10/19/2022
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 * This is a class declaration for a DatumStack. A DatumStack is 
 * simply just a vector(arraylist) of Datum elements. The vector of elements is
 * a private member of a class while there are various functions to manipulate
 * the stack or create a new one
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <vector>
#include "Datum.h"

using namespace std;

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum data[], int size);
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum newDatum);

private:
    vector<Datum> stack;
};

#endif