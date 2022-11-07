/*
 *  RPNCalc.cpp
 *  Charles Mitchell
 *  10/26/2022
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 * Function definitions for the RPNCalc class. There are various functions in
 * this class that manipulate the DatumStack and computer operations on
 * Datum objects and prints the top of the stack. 
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include "RPNCalc.h"

using namespace std;


/*
 * name:      RPNCalc default constructor
 * purpose:   calls the run function on RPNCalc
 * arguments: none
 * returns:   none
 * effects:   none
 */
RPNCalc::RPNCalc()
{
    run();
}


/*
 * name:      run
 * purpose:   calls the runImplement function on RPNCalc
 * arguments: none
 * returns:   none
 * effects:   none
 */
void RPNCalc::run()
{
    runImplement(cin);
}


/*
 * name:      runImplement
 * purpose:   starts a command loop for all operations made in other functions
 * arguments: istream for reading in commands in various ways
 * returns:   none
 * effects:   manipulates DatumStack with various operations
 */
void RPNCalc::runImplement(istream &input)
{
    int data;

    while (input >> com) {
        try {
            if (com == "#t" or com == "#f") {
                createBool(com);
            } else if (com == "not") {
                swapBool();
            } else if (com == "print") {
                print();
            } else if (com == "clear") {
                clear();
            } else if (com == "drop") {
                drop();
            } else if (com == "dup") {
                duplicate();
            } else if (com == "swap") {
                swapTop();
            } else if (com == "+" or com == "-" or com == "*" or com == "/" 
                    or com == "mod") {
                operCompute(com);
            } else if (com == "<" or com == ">" or com == "<=" or 
                    com == ">=" or com == "==") {
                operCompare(com);
            } else if (com == "{") {
                createRString(input);
            } else if (com == "quit") {
                cerr << "Thank you for using CalcYouLater." << endl;
                return;
            } else if (got_int(com, &data)) {
                createNum(com);
            } else if (com == "exec") {
                execute(stack.top().getRString());
            } else if (com == "file") {
                file();
                return;
            } else if (com == "if") {
                ifCommand();
            } else {
                cerr << com << ": unimplemented" << endl;
            }
        } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
    }
}


/*
 * name:      createNum
 * purpose:   creates a Datum integer object
 * arguments: input to turn into an integer variable
 * returns:   none
 * effects:   adds a Datum integer to DatumStack
 */
void RPNCalc::createNum(string input)
{
    int integer;

    if (got_int(input, &integer) == true) {
        Datum data = Datum(integer);
        stack.push(data);
    }
}


/*
 * name:      createBool
 * purpose:   creates a Datum bool object
 * arguments: input to turn into an bool variable
 * returns:   none
 * effects:   adds a Datum bool to DatumStack
 */
void RPNCalc::createBool(string input)
{
    if (input == "#t") {
        Datum data = Datum(true);
        stack.push(data);
    } else if (input == "#f") {
        Datum data = Datum(false);
        stack.push(data);
    }
}


/*
 * name:      createRString
 * purpose:   creates a Datum rstring object
 * arguments: input to turn into an rstring variable
 * returns:   none
 * effects:   adds a Datum rstring to DatumStack
 */
void RPNCalc::createRString(istream &input)
{   
    string rstring = parseRString(input);
    Datum data = Datum(rstring);
    stack.push(data);
}


/*
 * name:      swapBool
 * purpose:   swaps to the bool value on the top of the stack
 * arguments: none
 * returns:   none
 * effects:   removes a Datum from DatumStack and pushes another on
 */
void RPNCalc::swapBool() 
{
    try {
        bool check = stack.top().getBool();

        if (check == true) {
            stack.pop();
            Datum data = Datum(false);
            stack.push(data);
        } else {
            stack.pop();
            Datum data = Datum(true);
            stack.push(data);
        }
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      print
 * purpose:   prints the top Datum object on the DatumStack if stack is not
 *            empty
 * arguments: none
 * returns:   none
 * effects:   shows users most recent Datum object pushed on DatumStack
 */
void RPNCalc::print() 
{
    try {
        cout << stack.top().toString() << endl;
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      createNum
 * purpose:   creates a Datum integer object
 * arguments: input to turn into an integer variable
 * returns:   none
 * effects:   adds a Datum integer to DatumStack
 */
void RPNCalc::clear()
{   
    try {
        stack.clear();
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      drop
 * purpose:   removes the top Datum object from DatumStack
 * arguments: none
 * returns:   none
 * effects:   makes the second Datum object on DatumStack the top value
 */
void RPNCalc::drop()
{
    try {
        stack.pop();
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      duplicate
 * purpose:   duplicates the to Datum object on the DatumStack
 * arguments: none
 * returns:   none
 * effects:   adds a copy of the top Datum Object on the DatumStack
 */
void RPNCalc::duplicate()
{
    try {
        stack.push(stack.top());
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      swapTop
 * purpose:   swaps the two top most Datum objects on the DatumStack
 * arguments: none
 * returns:   none
 * effects:   makes the top Datum object the second and the second Datum object
 *            the first
 */
void RPNCalc::swapTop()
{
    try {
        Datum one = stack.top();
        stack.pop();
        Datum two = stack.top();
        stack.pop();

        stack.push(one);
        stack.push(two);
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      operCompute
 * purpose:   performs addition, subtraction, multiplication, division, or 
 *            remainder (mod) on two top most Datum integers on DatumStack
 *            if they are integers
 * arguments: operation to be performed on two integers
 * returns:   none
 * effects:   removes two top most integers from DatumStack and pushes the 
 *            the result of their given operation on the stack
 */
void RPNCalc::operCompute(string operate)
{
    try {
        int one = stack.top().getInt();
        stack.pop();
        int two = stack.top().getInt();
        stack.pop();
        int three;

        /* the two outside conditonals are used to check for division or mod
        on 0*/
        if (one == 0 and (operate == "/" or operate == "mod")) {
            cerr << "Error: division by 0." << endl;
            return;
        } else {
            if (operate == "+") {
                three = one + two;
            } else if (operate == "-") {
                three = two - one;
            } else if (operate == "*") {
                three = one * two;
            } else if (operate == "/") {
                three = two / one;
            } else {
                three = two % one;
            }
        }

        Datum data = Datum(three);
        stack.push(data);
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      operCompare
 * purpose:   compares two top most Datum integers on DatumStack
 *            if they are integers or if they are the same
 * arguments: comparsion operation to be performed on two integers or two same
 *            Datum objects on the DatumStack
 * returns:   none
 * effects:   removes two top most Datum Objects from DatumStack and pushes the 
 *            the result of their given comparison on the stack. This would be
 *            true or false
 */
void RPNCalc::operCompare(string operate)
{
    try {
        Datum one = stack.top();
        stack.pop();
        Datum two = stack.top();
        stack.pop();
        Datum t = Datum(true);
        Datum f = Datum(false);
        int num1;
        int num2;

        /* the two outside conditonals are used to control how we compare
        Datum objects as you can only compare integers in size, but we can also
        compre other Datums for equality*/
        if (got_int(one.toString(), &num1) and got_int(two.toString(), &num2)){
            int numone = one.getInt();
            int numtwo = two.getInt();

            if (operate == "<") {
                if (numtwo < numone) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            } else if (operate == ">") {
                if (numtwo > numone) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            } else if (operate == "<=") {
                if (numtwo <= numone) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            } else if (operate == ">=") {
                if (numtwo >= numone) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            } else if (operate == "==") {
                if (numtwo == numone) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            }
        } else {
            if (operate == "==") {
                if (two == one) {
                    stack.push(t);
                } else {
                    stack.push(f);
                }
            }
        }
    } catch (const exception &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}


/*
 * name:      execute
 * purpose:   executes order of commands in a given rstring
 * arguments: rstring to be turned into commands to execute on the command loop
 * returns:   none
 * effects:   removes top Datum object if an rstring and runs its commands and
 *            pushes it results from the commands on the DatumStack
 */
void RPNCalc::execute(string operate)
{
    try {
        string rstring = operate;

        /*this automaticallt removes the brackets and outside spaces from 
        rstring */
        string newstring = rstring.substr(2, rstring.length() - 4);
        stack.pop();
        
        /* reads every substring in rstring into command loop*/
        stringstream ss(newstring);
        runImplement(ss);
    } catch (...) {
        cerr << "Error: cannot execute non rstring" << endl;
    }
}


/*
 * name:      file
 * purpose:   reads in commands from file and executes them
 * arguments: none
 * returns:   none
 * effects:   removes top Datum object if an rstring with file name and runs 
 *            its commands and pushes it results from the commands on the 
 *            DatumStack
 */
void RPNCalc::file()
{
    if (not stack.top().isRString()) {
        cerr << "Error: file operand not rstring" << endl;
    } else {
        ifstream infile;
        string file = stack.top().getRString();

        /*this automaticallt removes the brackets and outside spaces from 
        rstring */
        string parsedFile = file.substr(2, file.length() - 4);

        infile.open(parsedFile);

        if (not infile.is_open()) {
            cerr << "Unable to read " << parsedFile << endl;
        } else {
            stack.pop();

            while (not infile.eof()) {
                runImplement(infile);
            }
        }
        infile.close();
        cerr << "Thank you for using CalcYouLater." << endl;
    }
} 


/*
 * name:      ifCommand
 * purpose:   performs in if statement on three uppermost Datum objects on
 *            DatumStack. Must be rstring, rstring, bool in that order
 * arguments: none
 * returns:   none
 * effects:   removes top three Datum objects if two rstrings and one bool and 
 *            if bool is true, execute second rstring, if bool is false, 
 *            execute first rstring
 */
void RPNCalc::ifCommand()
{
    string f_case;
    string t_case;
    bool test_case;

    if (stack.top().isRString()) {
        f_case = stack.top().getRString();
        stack.pop();
    } else {
        cerr << "Error: expected rstring in if branch" << endl;
        return;
    }

    if (stack.top().isRString()) {
        t_case = stack.top().getRString();
        stack.pop();
    } else {
        cerr << "Error: expected rstring in if branch" << endl;
        return;
    }

    if (stack.top().isBool()) {
        test_case = stack.top().getBool();
    } else {
        cerr << "Error: expected boolean in if test" << endl;
        return;
    }

    if (test_case) {
        execute(t_case);
    } else {
        execute(f_case);
    }
}

/*
 * name:      got_int
 * purpose:   checks to see if a string is an integer and it so turns it into 
 *            an integer
 * arguments: string to test and integer to store prospective results
 * returns:   true or false
 * effects:   sets an integer equal to the integer in the string if the string
 *            is an integer
 */
bool RPNCalc::got_int(string s, int *resultp)
{
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}


/*
 * name: parseRString
 * purpose: parses an input stream into a rstring (C++ string)
 * arguments: istream input
 * returns: a rstring
 * effects: none
 */
std::string RPNCalc::parseRString(std::istream &input)
{
    string returnString = "{ ";
    string readIn = "";
    bool check = true;
    int counter = 1;

    input >> readIn;
    

    while (check == true) {
        if (readIn == "}") {
            counter--;
        } else if (readIn == "{") {
            counter++;
        }

        if (counter == 0) {
            returnString += readIn;
            check = false;
        } else {
            returnString += readIn + " ";
            input >> readIn;
        }
    }

    return returnString;
}

