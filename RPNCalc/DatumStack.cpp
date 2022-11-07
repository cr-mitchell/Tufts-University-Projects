/*
 *  DatumStack.cpp
 *  Charles Mitchell
 *  10/19/2022
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 * Function definitions for the DatumStack class. There are various 
 * functions that manipulate the stack and creates new stacks.
 *
 */

#include <iostream>
#include <vector>
#include "DatumStack.h"

using namespace std;


/*
 * name:      DatumStack default constructor
 * purpose:   Create an empty vector of Datum objects
 * arguments: none
 * returns:   none
 * effects:   initalizes empty vector
 */
DatumStack::DatumStack()
{
    vector<Datum> construct = stack;
}


/*
 * name: DatumStack constructor 2
 * purpose:  initalizes a DatumStack and pushes back datum from a datum array
 * arguments: array of Datum elements, size of array
 * returns: none
 * effects: makes new DatumStack with datum elements
 */
DatumStack::DatumStack(Datum data[], int size)
{

    for (int i = 0; i < size; i++) {
        stack.push_back(data[i]);
    }
}


/*
 * name: isEmpty
 * purpose:  check to see if stack is empty
 * arguments: none
 * returns: true is stack is empty, false if not
 * effects: none
 */
bool DatumStack::isEmpty()
{
    return stack.empty();
}


/*
 * name: clear
 * purpose:  removes the all Datum elements on the stack
 * arguments: none
 * returns: none
 * effects: shrinks the stack size to 0;
 */
void DatumStack::clear()
{
    int size = stack.size();

    for (int i = 0; i < size; i++) {
        stack.pop_back();
    }
}


/*
 * name: size
 * purpose: returns the current size of the stack
 * arguments: none
 * returns: current size of stack
 * effects: none
 */
int DatumStack::size()
{
    return stack.size();
}


/*
 * name: top
 * purpose:  returns to the current top of the stack
 * arguments: none
 * returns: Datum element at the top of the stack
 * effects: none
 */
Datum DatumStack::top() 
{
    if (stack.empty() == true) {
        throw std::runtime_error("empty_stack");
    }
    return stack.back();
}


/*
 * name: pop
 * purpose:  removes the top Datum element on the stack
 * arguments: none
 * returns: none
 * effects: shrinks the stack size by 1
 */
void DatumStack::pop()
{
    if (stack.empty() == true) {
        throw std::runtime_error("empty_stack");
    }

    stack.pop_back();
}


/*
 * name: push
 * purpose:  adds a new Datum element to the top of the stack
 * arguments: a new Datum element
 * returns: none
 * effects: grows the stack size by 1
 */
void DatumStack::push(Datum newData)
{
    stack.push_back(newData);
}