/*  HuffmanCoder.h
 *  Charles Mitchell
 *  11/17/2022
 *
 *  CS 15 Proj 3 Zap
 *
 * This is a class declaration for a HuffmanCoder. The class contains two 
 * public methods that either convert a given file into a compressed file
 * and vise versa. The class also contains 6 private functions that compress
 * or decompress the files contents.
 */

#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H

#include <iostream>
#include <map>
#include "HuffmanTreeNode.h"
using namespace std;

class HuffmanCoder {
public:
    void encoder(string input_file, string output_file);
    void decoder(string input_file, string output_file);

private:
    map<char, int> count_freqs(std::istream &text, int &length, string &input);
    map<char, string> char_codes(HuffmanTreeNode *root, string &serialize, 
                                 map<char, string> &results);
    string decode(HuffmanTreeNode *root, string unbitstring);
    string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserialize_tree(std::string serialize_tree);
    HuffmanTreeNode *helper(int &pos, string serialize_tree);
};

#endif