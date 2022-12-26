/*
 *  unit_tests.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/05/22
 *
 *  CS 15 Proj 4
 *
 *  A unit testing file for...
 *
 */

#include "stringProcessing.h"
// #include "FSTreeTraversal.h"
#include "DirNode.h"
#include "FSTree.h"


#include <cassert>
#include <sstream>
#include <iostream>
#include <string>



using namespace std;

void stringParserTestOne() {

    string testString = "!!!Cs-15###";
    string result = stripNonAlphaNum(testString); 
    assert(result == "Cs-15");
}

void stringParserTestTwo() {

    string testString = "Cs-15###";
    string result = stripNonAlphaNum(testString); 
    assert(result == "Cs-15");}

void stringParserTest3() {

    string testString = "Cs-15";
    string result = stripNonAlphaNum(testString); 
    assert(result == "Cs-15");
}

void stringParserTest4() {

    string testString = "###Cs-15";
    string result = stripNonAlphaNum(testString); 
    assert(result == "Cs-15");
}

void stringParserTest5() {

    string testString = "";
    string result = stripNonAlphaNum(testString); 
    assert(result == "");
}



void stringParserTest6() {

    string testString = "!!!";
    string result = stripNonAlphaNum(testString); 
    assert(result == "");
}



// size for FSTree

void FstreeTest() {

}