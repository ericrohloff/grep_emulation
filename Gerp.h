/*
 * Gerp.h
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/3/2023
 * CS15 Project: gerp
 *
 * Header file for the gerp class which handles the functions required to run
 * the main command loop for the program. 
 *
 */

#ifndef _GERP_H_ 
#define _GERP_H_

#include <string>
#include <fstream>
#include <vector>
#include "StringMap.h"
#include "Line.h"
#include "DirNode.h"

using namespace std;

class Gerp {
public:
    Gerp(string directory, string outputFilename);
    ~Gerp();
    void run();

private:
    string directory;
    ofstream outputFile;

    // all case-insensitive words
    StringMap std_map;
    // all variations of words
    StringMap raw_map;

    // stores all pointers to Line objects for cleanup
    vector<Line*> lines;

    void buildIndex(string directory);
    void recurseDir(DirNode *n, string path);
    void indexFile(string path);
    void indexWord(const string &word, Line *line); 
 
    void anyString(string word);
    void insensitiveAnyString(string word);
    void changeOutputFile(string newFilename);

};

#endif