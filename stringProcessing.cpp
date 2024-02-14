/*
 * stringProcessing.cpp
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 11/30/2023
 * COMP 15 project gerp
 *
 * implementation for stripNonAlphaNum
 * which strips leading and trailing non-alphanumeric characters
 *
 */

#include "stringProcessing.h"

/*
 * name: stripNonAlphaNum(string input)
 * description: strips leading and trailing non alphanumeric characters
 * arguments: string input
 * returns: string
 * effects: reduces string to string of only alphanumeric characters as at the 
 *          start and end of the string
 */
string stripNonAlphaNum(string input)
{
    string word = "";

    int start = 0;
    int end = input.length()-1;

    while(not isalnum(input[start]) and start < input.length())
    {
        start++;
    }

    while(end >= 0 and not isalnum(input[end]))
    {
        end--;
    }

    for(int i = start; i <= end; i++)
    {
        word += input[i];
    }
    return word;
}

/*
 * name: toLowerCase
 * description: converts all characters to lower case
 * arguments: string input
 * returns: string
 * effects: converts string to lowercase
 */
string toLowerCase(string input) {
    string output = "";
    for (int i = 0; i < input.length(); i++) {
        output += tolower(input[i]);
    }
    return output;
}