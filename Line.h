/*
 * Line.h
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/5/2023
 * CS15 Project: gerp
 *
 * The Line struct is responsible for storing information necessary for
 * outputting query results.
 */

#ifndef _LINE_H_
#define _LINE_H_

#include <string>

using namespace std;

struct Line {
    string filepath;
    string line;
    int line_number;
};

#endif