/*
 * stringProcessing.h
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/12/2023
 *
 * CS15: Project gerp
 * 
 * Header file for string processing helper functions. stripNonAlphaNum is
 * responsible for removing all uncessary leading and trailing characters
 * from a word
 *
 */


#include <string>

using namespace std;

string stripNonAlphaNum(string input);

string toLowerCase(string input);