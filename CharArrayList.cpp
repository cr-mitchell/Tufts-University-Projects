/*
 *  CharArrayList.cpp
 *  Charles Mitchell
 *  09/20/2022
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Function definitions for the CharArrayList
 *
 */

#include "CharArrayList.h"
#include <sstream>
#include <stdexcept>

using namespace std;


/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: none
 * returns:   none
 * effects:   currsize and capcacity get 0;
 */
CharArrayList::CharArrayList()
{
    data = nullptr;
    currsize = 0;
    capacity = 0;
}


/*
 * name:      CharArrayList constructor 2
 * purpose:   initializes a CharArrayList of size 1 and adds 1 character
 * arguments: a character
 * returns:   none
 * effects:   increases the capacity and currsize of CharArrayList to 1
 */
CharArrayList::CharArrayList(char c)
{
    capacity = 1;
    currsize = 1;

    data = new char[capacity];
    data[0] = c;

}


/*
 * name:      CharArrayList constructor 3
 * purpose:   initializes a CharArrayList of inputted size and copies a
 *             given array into the CharArrayList
 * arguments: an array of characters, an integer that is the size of the array
 * returns:   none
 * effects:   increases the capacity and currsize of CharArrayList to size of arr
 */
CharArrayList::CharArrayList(char arr[], int size)
{
    capacity = size;
    currsize = size;

    data = new char[capacity];

    for (int i = 0; i < capacity; i++) {
        data[i] = arr[i];
    }
}


/*
 * name:      CharArrayList copy constructor
 * purpose:   A copy constructor for the class that makes a deep copy of a given
 *               instance
 * arguments:   address of CharArrayList 
 * returns: none
 * effects:   creates a copy of CharArrayList
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    data = new char[other.capacity];

    for (int i = 0; i < other.currsize; i++) {
        data[i] = other.data[i];
    }
} 


/*
 * name:      CharArrayList destructor
 * purpose:   free memory associated with the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   frees memory allocated by CharArraylist instances
 */
CharArrayList::~CharArrayList()
{
    delete [] data;
    data = nullptr;
}


/*
 * name:      CharArrayList Operator
 * purpose:   Define an assignment operator for the class that recycles the storage
 *             associated with the instance on the left of the assignment and makes
 *             a deep copy of the instance on the right hand side into the instance
 *              on the left hand side.
 * arguments: address of CharArrayList 
 * returns:   none
 * effects:   deep copies a instance
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other)
{
    if (this == &other) {
        return *this;
    }

    data = new char[other.capacity];

    for (int i = 0; i < other.currsize; i++) {
        data[i] = other.data[i];
    }

    currsize = other.currsize;
    capacity = other.capacity;
    return *this;

} 


/*
 * name: isEmpty
 * purpose:  checks if this specific instance of the class is empty (has no
 *          characters)
 * arguments: none
 * returns:   a boolean expression 
 * effects:   none
 */
bool CharArrayList::isEmpty() const
{
    return (currsize == 0);
}


/*
 * name: clear
 * purpose:  makes the instance into an empty array list
 * arguments: none
 * returns: none
 * effects: capacity and currsize get 0;
 */
void CharArrayList::clear()
{
    capacity = 0;
    currsize = 0;

    char *new_data = new char[capacity];

    delete [] data;
    data = new_data;
}


/*
 * name: size
 * purpose: returns current size of an instance of CharArrayList
 * arguments: none
 * returns: integer of elements in an instance of CharArrayList
 * effects: none
 */
int CharArrayList::size() const
{
    return currsize;
}


/*
 * name: first
 * purpose: gets the first element of an instance of CharArrayList
 * arguments: none
 * returns: first character in CharArrayList
 * effects: none
 */
char CharArrayList::first() const
{
    if (data == nullptr) {
        throw std::runtime_error("cannot get first of empty ArrayList");
    } else {
        return data[0];
    }
}


/*
 * name: last
 * purpose: gets the last element of an instance of CharArrayList
 * arguments: none
 * returns: last character in CharArrayList
 * effects: none
 */
char CharArrayList::last() const
{
    if (data == nullptr) {
        throw std::runtime_error("cannot get last of empty ArrayList");
    }
    
    return data[currsize - 1];
}


/*
 * name: elementAt
 * purpose: gets the given element of an instance of CharArrayList
 * arguments: index of choice in CharArrayList
 * returns: character in CharArrayList at given index
 * effects: none
 */
char CharArrayList::elementAt(int index) const
{
    if (index > currsize or index < 0) {
        throw std::range_error("index (" +
        to_string(index) + ") not in range [0.." +
        to_string(currsize) + ")");
    }
    
    return data[index];
}


/*
 * name:      toString
 * purpose:   turns the CharArrayList into a string, and returns it
 * arguments: none
 * returns:   a string representation of CharArrayLisy
 * effects:   none
 */
std::string CharArrayList:: toString() const
{
    std::stringstream ss;

    ss << "[CharArrayList of size " << currsize << " <<";

    for (int i = 0; i < currsize; i++) {
        ss << data[i];
    }

    ss << ">>]";

    return ss.str();
}

/*
 * name:      toReverseString
 * purpose:   turns the CharArrayList into a string in reverse, and returns it
 * arguments: none
 * returns:   a reverse string representation of CharArrayLisy
 * effects:   none
 */
std::string CharArrayList:: toReverseString() const
{
    std::stringstream ss;

    ss << "[CharArrayList of size " << currsize << " <<";

    for (int i = currsize - 1; i > - 1; i--) {
        ss << data[i];
    }

    ss << ">>]";

    return ss.str();
}


/*
 * name:      pushAtBack
 * purpose:   push the provided character into the back of the CharArrayList
 * arguments: a character to add to the back of the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::pushAtBack(char c)
{
    if (currsize == capacity) {
        expand();
    }

    data[currsize] = c;
    currsize++;
}


/*
 * name:      pushAtFront
 * purpose:   push the provided character into the front of the CharArrayList
 * arguments: a character to add to the front of the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::pushAtFront(char c)
{
    if (currsize == capacity) {
        expand();
    }

    char *new_data = new char[capacity];
    
    new_data[0] = c;

    for (int i = 0; i < currsize; i++) {
        new_data[i + 1] = data[i];
    }

    delete [] data;
    data = new_data;

    currsize++;
}


/*
 * name:      insertAt
 * purpose:   push the provided character into the given index of the CharArrayList
 * arguments: a character to add to the given index of the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::insertAt(char c, int index)
{
    if (index > currsize or index < 0) {
        throw std::range_error("index (" +
        to_string(index) + ") not in range [0.." +
        to_string(currsize) + "]");
    }

    if (currsize == capacity) {
        expand();
    }

    for (int i = currsize; i > index; i--) {
        data[i] = data [i - 1];
    }

    data[index] = c;
    currsize++;
}


/*
 * name:      insertInOrder
 * purpose:   push the provided integer into ASCII value order in the CharArrayList
 * arguments: a character to add to the ASCII value order in the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::insertInOrder(char c)
{
    if (currsize == capacity) {
        expand();
    }

    char *new_data = new char[capacity];
    int counter = 0;

    for (int i = 0; i < currsize; i++) {
        if (data[i] >= c)
        {
            break;
        }
        counter++;
    }

    for (int j = 0; j < counter; j++) {
        new_data[j] = data[j];
    }

    new_data[counter] = c;

    for (int k = counter; k < currsize; k++) {
        new_data[k + 1] = data[k];
    }

    delete [] data;
    data = new_data;

    currsize++;
}


/*
 * name:      popFromFront
 * purpose:   remove the first item from the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   decreases num items of CharArrayList by 1
 *            removes the last item from the list
 */
void CharArrayList::popFromFront()
{
    if (data == nullptr) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }

    char *new_data = new char[capacity];

    for (int i = 1; i < currsize; i++) {
        new_data[i - 1] = data[i];
    }

    delete [] data;
    data = new_data;

    currsize--;
}


/*
 * name:      popFromBack
 * purpose:   remove the last item from the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   decreases num items of CharArrayList by 1
 *            removes the last item from the list
 */
void CharArrayList::popFromBack()
{
    if (data == nullptr) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }

    char *new_data = new char[capacity];

    for (int i = 0; i < currsize - 1; i++) {
        new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;

    currsize--;
    
}


/*
 * name:      removeAt
 * purpose:   remove the item from the CharArrayList at given index
 * arguments: index of choice in CharArrayList
 * returns:   none
 * effects:   decreases num items of CharArrayList by 1
 *            removes the indexed item from the list
 */
void CharArrayList::removeAt(int index)
{
    if (index > currsize or index < 0) {
        throw std::range_error("index (" +
        to_string(index) + ") not in range [0.." +
        to_string(currsize) + ")");
    }

    currsize--;
    char *new_data = new char[capacity];

    for (int i = 0; i < index; i++) {
        new_data[i] = data[i];
    }


    for (int j = index; j < currsize; j++) {
        new_data[j] = data[j + 1];
    }

    delete [] data;
    data = new_data;
}


/*
 * name:      replaceAt
 * purpose:   replace the item from the CharArrayList at given index with a new given char
 * arguments: index of choice in CharArrayList and new character of choice
 * returns:   none
 * effects:   replaces an element in the CharArrayList
 */
void CharArrayList::replaceAt(char c, int index)
{
    if (index > currsize or index < 0) {
        throw std::range_error("index (" +
        to_string(index) + ") not in range [0.." +
        to_string(currsize) + ")");
    }

    char *new_data = new char[capacity];

    for (int i = 0; i < index; i++) {
        new_data[i] = data[i];
    }

    new_data[index] = c;

    for (int j = index + 1; j < currsize; j++) {
        new_data[j] = data[j];
    }

    delete [] data;
    data = new_data;
}


/*
 * name:      concatenate
 * purpose:   adds one CharArrayList with another one to create one CharArrayList
 * arguments: a pointer to a second CharArrayList
 * returns:   none
 * effects:   increases current size and, in some capacity, by size of pointer CharArrayList
 */
void CharArrayList::concatenate(CharArrayList *other)
{
    const int newsize = other->size();

    for (int i = 0; i < newsize; i++) {
        pushAtBack(other->elementAt(i));
    }
}


/*
 * name:      shrink
 * purpose:   decreases the capacity of the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   creates new, smaller array on heap, copies over elements,
 *            and recycles the old array
 */
void CharArrayList::shrink()
{
    char *new_data = new char[currsize];

    for (int i = 0; i < currsize; i++) {
        new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;

    capacity = currsize;
}


/*
 * name:      expand
 * purpose:   increase the capacity of the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   creates new, larger array on heap, copies over elements,
 *            and recycles the old array
 */
void CharArrayList::expand()
{
    capacity = 2 + capacity * 2;

    char *new_data = new char[capacity];
    
    for (int i = 0; i < currsize; i++) {
        new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;
}
