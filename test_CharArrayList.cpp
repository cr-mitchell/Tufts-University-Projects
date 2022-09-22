/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */

#include "CharArrayList.h"
#include <cassert>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

//tests to see if the default constructor creates an empty CharArrayList
void constructor_test_0() {
    CharArrayList test;
}

//tests to see if the default constructor creates an empty CharArrayList
void constructor_test_1() {
    CharArrayList test;
    assert(test.size() == 0);
}

//tests to see if the 3rd constructor copies an array into a CharArrayList
void constructor_test_2() {
    char arr[] = {'a', 'b', 'c'};
    CharArrayList test(arr, 3);
    assert(test.size() == 3);
    assert(test.elementAt(2) == 'c');
}

//tests to see if the 2nd constructor creates a CharArrayList with given char
void constructor_test_3() {
    CharArrayList test('a');
    assert(test.size() == 1);
    assert(test.elementAt(0) == 'a');
}

//tests to see if isEmpty returns true if a CharArrayList is empty
void isEmpty_test() {
    CharArrayList test;
    assert(test.isEmpty() == true);
} 

//tests to see if clear empties a filled CharArrayList
void clear_test() {
    CharArrayList test;
    test.pushAtBack('k');
    test.pushAtBack('r');
    test.clear();
    assert(test.size() == 0);
}

//tests to see if size returns the correct size of a CharArrayList
void size_test() {
    CharArrayList test;
    assert(test.size() == 0);
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test1(arr, 4);
    assert(test1.size() == 4);
}

//tests to see if first returns the first char in a CharArrayList
//also tests to see if runtime_error gets thrown if CharArrayList is empty
void first_test() {
    CharArrayList test;
    test.pushAtBack('k');
    test.pushAtFront('r');
    assert(test.first() == 'r');

    /////////////////////////////////////////

    CharArrayList test1;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test1.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");
}

//tests to see if last returns the last char in a CharArrayList
//also tests to see if runtime_error gets thrown if CharArrayList is empty
void last_test() {
    CharArrayList test;
    test.pushAtBack('k');
    test.pushAtFront('r');
    assert(test.last() == 'k');

    //////////////////////////////////////

    CharArrayList test1;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test1.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}

//tests to see if elementAt returns the char in a CharArrayList at a given index
//also tests to see if range_error gets thrown if the given index is out of range of current size
void elementAt_test() {
    CharArrayList test;
    test.pushAtBack('k');
    test.pushAtFront('r');
    test.pushAtBack('a');
    test.pushAtBack('s');
    assert(test.elementAt(2) == 'a');
    assert(test.elementAt(0) == 'r');
    assert(test.elementAt(3) == 's');

    /////////////////////////////////////////////

    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test1(arr, 8);

    bool range_error_thrown = false;

    std::string error_message = "";

    try {
        test1.elementAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8)");
}

//tests to see if toString turns an instance of CharArrayList into a string
void toString_test() {
    CharArrayList test;
    test.pushAtBack('1');
    test.pushAtBack('2');
    test.pushAtBack('3');
    assert(test.toString() == "[CharArrayList of size 3 <<123>>]");
}

//tests to see if toReverseString turns an instance of CharArrayList into a string in reverese
void toReverseString_test() {
    CharArrayList test;
    test.pushAtBack('1');
    test.pushAtBack('2');
    test.pushAtBack('3');
    assert(test.toReverseString() == "[CharArrayList of size 3 <<321>>]");
}

//tests to see if pushAtBack adds an element to the last current size index in an instance of CharArrayList
void pushAtBack_test() {
    CharArrayList test;
    test.pushAtBack('a');
    test.pushAtBack('b');
    test.pushAtBack('c');
    assert(test.elementAt(2) == 'c');
}

//tests to see if pushAtFront adds an element to the first current size index in an instance of CharArrayList
void pushAtFront_test() {
    CharArrayList test;
    test.pushAtFront('a');
    test.pushAtFront('b');
    test.pushAtFront('c');
    assert(test.elementAt(0) == 'c');
}

//tests to see if insertAt adds an element at a given index in an instance of CharArrayList
void insertAt_test() {
    char arr[] = {'a', 'b', 'd', 'e'};
    CharArrayList test(arr, 4);
    test.insertAt('c', 2);
    assert(test.elementAt(2) == 'c');
    assert(test.elementAt(0) == 'a') ;
    assert(test.elementAt(4) == 'e');  

    //////////////////////////////////////

    CharArrayList test1(arr, 4);

    bool range_error_thrown = false;

    std::string error_message = "";

    try {
        test1.insertAt('z', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..4]"); 
}

//tests to see if insertInOrder adds an element at ASCII value order to certain instance in CharArrayList
void insertInOrder_test() {
    char arr[] = {'a', 'b', 'd', 'e'};
    CharArrayList test(arr, 4);
    test.insertInOrder('c');
    assert(test.elementAt(2) == 'c');
    assert(test.size() == 5);

    ///////////////////////////////////////

    char arr1[] = {'b', 'c', 'd', 'e'};
    CharArrayList test1(arr1, 4);
    test1.insertInOrder('a');
    assert(test1.elementAt(0) == 'a');

    ///////////////////////////////////////

    char arr2[] = {'a', 'b', 'c', 'd'};
    CharArrayList test2(arr2, 4);
    test2.insertInOrder('e');
    assert(test2.elementAt(4) == 'e');
}

//tests to see if popFromFront removes an element from the front of an instance of CharArrayList
//also tests to see if runtime_error gets thrown if CharArrayList is empty
void popFromFront_test() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test(arr, 4);
    test.popFromFront();
    assert(test.elementAt(0) != 'a');
    assert(test.size() == 3);

    ///////////////////////////////////////

    CharArrayList test1;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test1.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

//tests to see if popFromBack removes an element from the back of an instance of CharArrayList
//also tests to see if runtime_error gets thrown if CharArrayList is empty
void popFromBack_test() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test(arr, 4);
    test.popFromBack(); 
    assert(test.size() == 3);

    //////////////////////////////////////////

    CharArrayList test1;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test1.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

//tests to see if removeAt removes an element from a given index of an instance of CharArrayList
//also tests to see if range_error gets thrown if the given index is out of range of current size
void removeAt_test() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test(arr, 4);
    test.removeAt(2); 
    assert(test.elementAt(2) == 'd');
    test.removeAt(0);
    assert(test.elementAt(0) == 'b');
    test.removeAt(1);
    assert(test.size() == 1);

    ////////////////////////////////////////

    CharArrayList test1(arr, 4);

    bool range_error_thrown = false;

    std::string error_message = "";

    try {
        test1.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..4)");
}

//tests to see if replaceAt replaces an element a given index of an instance of CharArrayList
//also tests to see if range_error gets thrown if the given index is out of range of current size
void replaceAt_test() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test(arr, 4);
    test.replaceAt('z', 2); 
    assert(test.elementAt(2) == 'z');
    test.replaceAt('x', 0); 
    assert(test.elementAt(0) == 'x');
    test.replaceAt('y', 3); 
    assert(test.elementAt(3) == 'y');

    /////////////////////////////////////////////

    CharArrayList test1(arr, 4);

    bool range_error_thrown = false;

    std::string error_message = "";

    try {
        test1.replaceAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..4)");
}

//test to see if concatenate adds to a pointer CharArrayList to the main CharArrayList
void concatenate_test() {
    CharArrayList test1;
    CharArrayList test2;
    test1.pushAtFront('a');
    test1.pushAtBack('b');
    test1.pushAtBack('c'); 
    test2.pushAtFront('a');
    test2.pushAtBack('b');
    test2.pushAtBack('c'); 
    test1.concatenate(&test2);
    assert(test1.elementAt(3) == 'a');
    assert(test1.size() == 6);

    //////////////////////////////////

    char arr[] = {'l', 'o', 'v', 'e'};
    CharArrayList test3(arr, 4);
    test3.concatenate(&test3);
    assert(test3.size() == 8);
}

//tests to see if shrink lowers the capacity to the current size of an instance of CharArrayList
void shrink_test() {
    char arr[] = {'a', 'b'};
    CharArrayList test(arr, 2);
    test.shrink();
    assert(test.size() == 2);
}

//tests to see if expand grows the capacity of an instance of CharArrayList
void expand_test() {
    CharArrayList test;
    test.pushAtBack('a');
    assert(test.size() == 1);
}
// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 
    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');                          
}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {
    
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front, back, and middle of a larger list.
void insertAt_front_back_middle() {
    
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);

        // insertAt middle
        test_list.insertAt('z', 3);

        assert(test_list.size() == 9);
        assert(test_list.elementAt(3) == 'z');
        assert(test_list.toString() == 
        "[CharArrayList of size 9 <<abczdefgh>>]");

        // insertAt front
        test_list.insertAt('y', 0);

        assert(test_list.size() == 10);
        assert(test_list.elementAt(0) == 'y');
        assert(test_list.toString() == 
        "[CharArrayList of size 10 <<yabczdefgh>>]");

        // insertAt back
        test_list.insertAt('x', 10);

        assert(test_list.size() == 11);
        assert(test_list.elementAt(10) == 'x');
        assert(test_list.toString() == 
        "[CharArrayList of size 11 <<yabczdefghx>>]");
        
}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
    
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]"); 
}
