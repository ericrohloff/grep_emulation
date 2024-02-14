/*
 * StringMap.h
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/10/2023
 *
 * CS15: Project gerp
 * 
 * Implementation of String map which functions as a map of strings
 *
 */
#ifndef _STRINGMAP_H_ 
#define _STRINGMAP_H_

#include <string>
#include <list>
#include <utility>
#include "Line.h"
#include <vector>

using namespace std;

typedef vector<Line*> Value;

class StringMap {
public:
    StringMap();
    ~StringMap();
// private:

    typedef list<pair<string, Value>> Bucket;

    Bucket *data;

    int capacity;
    int size;

    
    void expand();
    void rehashBucket(const Bucket &bucket, Bucket *newData);

    int hashIndex(const string &key);


    void insert(const string &key, Line *line);
    Value *get(const string &key);
    bool contains(string key);

};


#endif