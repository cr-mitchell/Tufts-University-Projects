/*
 *  FSTreeTraversal.cpp
 *  Charles Mitchell, Rofeeah Ayeni
 *  12/14/22
 *
 *  CS 15 Project 4 — Gerp
 *
 *  Description: Function defintions for the FSTreeTraversal class. On running,
 *  an instance of FSTree is made with the users inputted directory. This 
 *  function populates a vector with the help of a recursive helper function.
 *
 */

#include "FSTreeTraversal.h"
using namespace std;


/* name: createTree
 * purpose: takes in a input directory and builds a tree with all 
 * subdirectories and files and calls a helper function to populate a vector
 * of structs with the file names and paths to get to that file
 * arguments: an input directory and vector of structs
 * returns: none
 * effects: populates the vector of stucts passed in by reference
 */
void FSTreeTraversal::createTree(string directory, 
                                             vector<FileData> &file_data) 
{
    FSTree ourTree(directory);
    string paths = "";
    printPaths(ourTree.getRoot(), paths, file_data);
}


/* name: printPaths
 * purpose: recursively travels through a tree of directories and files
 * and puts the path to the file and the file name into a struct instance
 * and then pushes onto the vector passed in by reference
 * arguments: a pointer to the root of the tree, a strings to concatenate the 
 * path names onto, and vector of structs
 * returns: none
 * effects: populates the vector of stucts passed in by reference
 */
void FSTreeTraversal::printPaths(DirNode *root, string paths, 
                                    vector<FileData> &file_data) 
{
    if (root->isEmpty()) {
        return;
    }

    paths += root->getName() + "/";
    if (root->hasSubDir()) {
        int subs = root->numSubDirs();
        //loop used because this is a n-ary tree, not a binary tree
        for (int i = 0; i < subs; i++) {
            printPaths(root->getSubDir(i), paths, file_data);
        }
    }
    
    if (root->hasFiles()) {
        int files = root->numFiles();
        for (int i = 0; i < files; i++) {
            string file_name = root->getFile(i);
            int size = paths.size();
            paths +=  file_name;
            int cut = paths.size();

            FileData temp;
            temp.file_name = file_name;
            temp.file_path = paths;
            file_data.push_back(temp); ;
            
            //cuts off the file last added to the path string
            for (int j = size; j < cut; j++) {
                paths.pop_back();
            }
        }
    }
}