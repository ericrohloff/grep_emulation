/*
 * unit_tests.h
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 11/30/2023
 *
 * CS15 Project: gerp
 *
 * Testing file for the ./gerp program. 
 * 
 * many of these tests are commented out because they worked with older
 * implementations of StringMap. Since then, we have removed templating and
 * simplified much of the code. Due to these earlier tests, we were able to
 * ensure that crucial parts of StringMap worked, even after we changed things
 * much of the later stage testing was done directly with diff tests
 * 
 * otherwise, also tests stripNonAlphaNum and toLowerCase functions
 *
 */

#include "stringProcessing.h"
#include "StringMap.h"
#include <cassert>
#include <vector>
#include <iostream>

// needed only for commented-out tests
// #include <unordered_map>
// #include <chrono>


using namespace std;

/* 
 * test all alphanumeric
 */
void test_all_alphanumeric() {
    string out = stripNonAlphaNum("hello");
    assert(out == "hello");
}

/* 
 * test basic non-alphanumeric
 */
void test_basic_non_alphanumeric() {
    string out = stripNonAlphaNum("##hello--world--&*#()");
    cout << out << endl;
    assert(out == "hello--world");
}

/* 
 * test if front and end work as intended
 */
void test_front_back(){
    string out = stripNonAlphaNum("-/@#$%^&*abcdef-/@#$%^&*");
    cout << out << endl;
    assert(out == "abcdef");
}

/* 
 * test comp15 string
 */
void test_comp15_string() {
    string out = stripNonAlphaNum("comp15");
    assert(out == "comp15");
}

/* 
 * no alphanumeric
 */
void no_alphanumeric() {
    string out = stripNonAlphaNum("#$()(*)#($*#)($)(#*$)()");
    assert(out == "");
}

/* 
 * test toLowerCase
 */
void test_toLowerCase() {
    assert("lower" == toLowerCase("LOweR"));
}

// (NEW) StringMap tests

// Test StringMap constructor
void test_constructor()
{
    StringMap test_1;
}

// Test StringMap insert and get
void insert_string_map()
{
    StringMap test;
    Line *newLine = new Line;
    cout << "inserting\n";
    test.insert("key", newLine);
    test.get("key");
    assert(test.get("key")->front() == newLine);
    delete newLine;
}

// (OLD) STRINGMAP testing functions
// (commented out due to changes in implementation/interface)

// /* 
//  * test constructor destructor
//  */
// void test_constructor_destructor() {
//     StringMap<string> map;
// }

// /*
//  *  insert a one
//  */
// void test_insert_one()
// {
//     StringMap<string> map;
//     string key = "bad";
//     map.insert(key, "bitches");
//     assert(*map.get("bad") == "bitches");
// }

/* 
 * test many inserts
 */
// void test_many_inserts() {
//     StringMap<string> map; 
//     string key = "a";

//     for (int i =0; i < 50; i++) {
//         key += char(('a' + i % 26));
//         cout << "inserting\n";
//         map.insert(key, key);
//         assert(*map.get(key) == key);
//     }

// }

// // TEST for inserting and getting values from map
// void test_insert_vector() {
//     StringMap<vector<string>> map;
//     string key = "bad";
//     vector<string> newvector;
//     map.insert(key, newvector);
//     vector<string> *crazy_lines = map.get(key);
//     crazy_lines->push_back("bitches");
//     assert(crazy_lines->back() == "bitches");
// }

// // void test_nested_vector() {
// //     StringMap<StringMap<vector<string>>> outer;
// //     outer.insert("key");
// //     StringMap<vector<string>> *crazy_map = outer.get("key");

// //     if (not crazy_map->contains("KEY")) {
// //         crazy_map->insert("KEY", "VALUE");
// //     }

// //     vector<string> *crazy_lines = crazy_map->get("KEY");
// //     cout << crazy_lines->size() << endl;
// // }


// this test was used to compare the speed of our implementation to the speed
// of unordered map when we were optimizing our stringmap implementation
// void test_maps() {
//     StringMap<string> ourMap;
//     unordered_map<string, string> goodMap;
    
//     string key = "a";

//     auto start = chrono::high_resolution_clock::now();

//     cout << "using our map\n";
//     for (int i =0; i < 5000; i++) {
//         ourMap.insert(key, key);
//     }

//     auto middle = chrono::high_resolution_clock::now();
//     cout << "done in " << (middle - start).count() << endl;

//     cout << "using their map\n";
//     for (int i =0; i < 5000; i++) {
//         goodMap[key] = key;
//     }
    
//     auto end = chrono::high_resolution_clock::now();

//     cout << "done in " << (end - middle).count() << endl;
// }