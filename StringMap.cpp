/*
 * StringMap.cpp
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/10/2023
 *
 * CS15: Project gerp
 * 
 * Implementation of String map which functions as a map of strings this can be
 * used to access the strings stored in the map.
 *
 */
#include "Line.h"
#include "StringMap.h"
#include <functional>
#include <iostream>

/*
 * name: StringMap()
 * description: default constructor
 * arguments: none
 * returns: none
 * effects: creates instance of the StringMap class which is a map. 
 */
StringMap::StringMap ()
{
    capacity = 8192;
    size = 0;
    data = new Bucket [capacity];
}

/*
 * name: insert(string key, T value)
 * description: inserts the string and associated key into the map.
 * arguments: string key, T value
 * returns: void
 * effects: inserts a new string and value pair into the map.
 */
void StringMap::insert(const string &key, Line *line)
{
    Value *to_insert = get(key);
    if (to_insert == nullptr) {
        // then we need to insert
        size++;
        float load_factor = float(size) / float(capacity);
        if (load_factor > 0.7) expand();

        int index = hashIndex(key);
        pair<string, Value> newPair;
        newPair.first = key;
        data[index].push_back(newPair);
        to_insert = &data[index].back().second;

    }
    if (to_insert->size() == 0)
    {
        to_insert->push_back(line);
    } else if (to_insert->back() != line)
    {
        to_insert->push_back(line);
    }
}

/*
 * name: ~StringMap()
 * description: Destructor for the StringMap
 * arguments: none
 * returns: none
 * effects: Deletes array which is the StringMap
 */
StringMap::~StringMap()
{
    delete [] data;
}

/*
 * name: expand()
 * description: expands the map to hold correct size of data needed to be stored
 * arguments: none
 * returns: void
 * effects: expands size of the array inside the Stringmap
 */
void StringMap::expand()
{
    int oldCapacity = capacity;
    capacity = capacity * 2 + 2;

    Bucket *newData = new Bucket[capacity];

    for (int i = 0; i < oldCapacity; i++) {
        rehashBucket(data[i], newData);
    }

    delete [] data;
    data = newData;
}

/*
 * name: rehashNode
 * description: rehashes function to handle collisions
 * arguments: ChainNode *n
 * returns: T
 * effects: rehash function so collisions are handled properly
 */

void StringMap::rehashBucket(const Bucket &bucket, Bucket *newData) {
    for (
        typename Bucket::const_iterator b = bucket.begin();
         b != bucket.end();
         ++b
    ) {
        int i = hashIndex(b->first);
        newData[i].push_back(*b);
    }
}

/*
 * name: get()
 * description: gets value based on key given 
 * arguments: string key
 * returns: T
 * effects: gets value at specific key of the map
 */

Value *StringMap::get(const string &key) {
    int index = hashIndex(key);
    if (key == "") { return nullptr;}
    for (typename Bucket::iterator b = data[index].begin(); 
        b != data[index].end(); ++b)
    {
        if (b->first == key)
        {
            return &b->second;
        }
    }
    return nullptr;
}

/*
 * name: hashIndex
 * description: returns index of the key
 * arguments: string key
 * returns: int
 * effects: gets index for specific key of the map
 */

int StringMap::hashIndex(const string &key) 
{
    return hash<string>{}(key) % capacity;
}