 /* HuffmanCoder.cpp
 *  Charles Mitchell
 *  11/17/2022
 *
 *  CS 15 Proj 3 Zap
 *
 * Function defintions for the HuffmanCoder class. On running, the user will
 * wither choose to compress a file and store its contents in another file or
 * decompress a file and store the conetns in another file. The two main 
 * functions that handle this is encoder and decoder with the help of their
 * helper functions which are called in them. 
 *
 */

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include "HuffmanCoder.h"
#include "BinaryIO.h"
using namespace std;


/* name: encoder
 * purpose: takes in a input file compresses its contents to a minimum number
 * of bytes and save those contents in an output file
 * arguments: an input file and an output file
 * returns: none
 * effects: takes the original string in the inputfile, compresses the string
 * into binary and stores it into an outputfile
 */
void HuffmanCoder::encoder(string input_file, string output_file)
{
    ifstream instream;
    instream.open(input_file);

    if (not instream.is_open()) {
        throw runtime_error("Unable to open file " + input_file);
    }

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
                    NodeComparator> my_pq;
    int length = 0;
    string sentence = "";
    map<char, int> results = count_freqs(instream, length, sentence);

    if (results.size() == 0) {
        throw runtime_error("Cannoy zap an empty file!");
    }

    map<char, int>::iterator check;

    for (check = results.begin(); check != results.end(); check++) {
        HuffmanTreeNode *newnode = new HuffmanTreeNode(check->first,
                                                        check->second);
        my_pq.push(newnode);
    }

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
                    NodeComparator> checksize = my_pq;
    int size = 0;
    int value = 0;

    while (checksize.size() != 0) {
        size += checksize.top()->get_freq();
        checksize.pop();
    }

    HuffmanTreeNode *root;

    while (value != size) {
        HuffmanTreeNode *one = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *two = my_pq.top();
        my_pq.pop();

        value = one->get_freq() + two->get_freq();

        root = new HuffmanTreeNode('\0', value);
        root->set_left(one);
        root->set_right(two);

        my_pq.push(root);
    }

    string bitstring = "";
    map<char, string> input;
    map<char, string> codes = char_codes(root, bitstring, input);

    int input_size = sentence.size();
    for (int i = 0; i < input_size; i++) {
        if (codes.find(sentence[i]) != codes.end()) {
            bitstring += codes.at(sentence[i]);
        }
    }
    string serial_tree = serialize_tree(root);

    BinaryIO write;
    write.writeFile(output_file, serial_tree, bitstring);

    cout << "Success! Encoded given text using " << bitstring.size() 
            << " bits." << endl;

    instream.close();
}


/* name: decoder
 * purpose: takes in a input file decompresses its contents from the 
 * minimum number of bytes and save those contents in an output file
 * arguments: an input file and an output file
 * returns: none
 * effects: takes the binary created in the encoder function in the inputfile, 
 * decompresses the binary into the original string and stores it into an 
 * outputfile
 */
void HuffmanCoder::decoder(string input_file, string output_file)
{
    BinaryIO read;
    vector<string> combo = read.readFile(input_file);
    string unserialize = combo.at(0);
    string unbitstring = combo.at(1);

    HuffmanTreeNode *root = deserialize_tree(unserialize);

    string og_string = decode(root, unbitstring);

    ofstream outstream;
    outstream.open(output_file);

    if (not outstream.is_open()) {
        throw runtime_error("Unable to open file " + output_file);
    }

    outstream << og_string;

    outstream.close();
}


/* name: char_codes
 * purpose: stores the amount of left and right turns it takes traversing 
 * through a binary tree to get to a particular character
 * arguments: pointer to root of binary tree, reference to a string, and a map
 * to store character in binary tree and the reference string that hold amount
 * of turns it took to get to character in the binary tree
 * returns: a map with characters and their binary codes
 * effects: none
 */
map<char, string> HuffmanCoder::char_codes(HuffmanTreeNode *root, 
                   string &serialize, map<char, string> &results)
{
    if (root->isLeaf()) {
        char value = root->get_val();
        results.insert(pair<char, string>(value, serialize));
    } else {
        if (root->get_left()) {
            char_codes(root->get_left(), serialize += "0", results);
            serialize.pop_back();
        }

        if (root->get_right()) {
            char_codes(root->get_right(), serialize += "1", results);
            serialize.pop_back();
        }
    }

    return results;
}


/* name: decode
 * purpose: travels through binary tree build orginal string from input file
 * arguments: pointer to root of binary tree, a string to concatenate on
 * returns: orginal string that was compressed
 * effects: none
 */
string HuffmanCoder::decode(HuffmanTreeNode *root, string unbitstring) 
{
    HuffmanTreeNode *check = root;
    int index = 0;
    string decoded = "";

    while (index < unbitstring.size()) {
        if (unbitstring[index] == '0') {
            check = check->get_left();
        } else if (unbitstring[index] == '1') {
            check = check->get_right();
        }

        if (check->isLeaf()) {
            decoded += check->get_val();
            check = root;
        } else if (not check->isLeaf() and index == (unbitstring.size() - 1)) {
            throw runtime_error("Encoding did not match Huffman tree.");
        }

        index++;
    }

    return decoded;
}


/* name: count_freqs
 * purpose: counts the frequencies of characters in a given file
 * arguments: input file, a reference to an integer to count size of string, 
 * a reference to a string to concatenate the input file text on
 * returns: a map with characters and their frequencies
 * effects: none
 */
map<char, int> HuffmanCoder::count_freqs(istream &text, int &size,
                                         string &input) 
{
    char curr;
    map<char, int> results;

    while (text.get(curr)) {
        size++;
        input.push_back(curr);
        if (results.find(curr) == results.end()) {
            results.insert(pair<char, int>(curr, 1));
        } else {
            results.find(curr)->second++;
        }
    }

    return results;
}


/* name: serialize_tree
 * purpose: concatenates on a string recursively to have a reference string
 * of what the binary tree looks like
 * arguments: a pointer to root of binary tree
 * returns: string that maps out binary tree
 * effects: none
 */
string HuffmanCoder::serialize_tree(HuffmanTreeNode *root)
{
    string serialize = "";

    if (root == nullptr) {
        return serialize;
    }

    if (root->isLeaf()) {
        serialize += "L";
        serialize.push_back(root->get_val());
    } else {
        serialize += "I";
    }

    return serialize + serialize_tree(root->get_left()) + 
    serialize_tree(root->get_right());

    return serialize;
}


/* name: deserialize_tree
 * purpose: calls helper function and initalizes position
 * arguments: string that maps out binary tree
 * returns: root to built binary tree
 * effects: none
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(string serialize_tree)
{
    int pos = 0;
    return helper(pos, serialize_tree);
}


/* name: helper
 * purpose: recursively builds a binary tree with string that maps out binary
 * tree 
 * arguments: string that maps out binary tree
 * returns: root to built binary tree
 * effects: none
 */
HuffmanTreeNode* HuffmanCoder::helper(int &pos, string serialize_tree)
{
    if (serialize_tree.size() - (pos + 1) == 0) {
        return nullptr;
    }

    HuffmanTreeNode *root;

    if (serialize_tree[pos] == 'I') {
        root = new HuffmanTreeNode('\0', 0);
        pos++;
    } else {
        char enter = serialize_tree[pos + 1];
        root = new HuffmanTreeNode(enter, 0);
        root->set_left(nullptr);
        root->set_right(nullptr);
        pos += 2;
        return root;
    }

    root->set_left(helper(pos, serialize_tree));
    root->set_right(helper(pos, serialize_tree));

    return root;
}
