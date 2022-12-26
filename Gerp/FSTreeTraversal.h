/*
 *  FSTreeTraversal.h
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: This is a class declaration for a FSTreeTraversal. This class
 *  contains one public and one private method and a declaration of a stuct. 
 *  The create tree function takes in the users inputed directory and a 
 *  vector of declared struct by reference and creates a tree of the given 
 *  directory and calls the private function to populate the vector. 
 *
 */

#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H

#include <iostream>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"
using namespace std;


struct FileData {
    string file_name;
    string file_path;
};

class FSTreeTraversal {
public:
    void createTree(string directory, vector<FileData> &file_data);
private:
    void printPaths(DirNode *root, string paths, vector<FileData> &file_data);
};

#endif