/*
 * Gerp.cpp
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/3/2023
 * CS15 Project: gerp
 *
 * Implementation of the gerp class which handles the functions required to run
 * the main command loop for the program. 
 *
 */

#include "Gerp.h"
#include "FSTree.h"
#include <iostream>
#include "stringProcessing.h"
#include <sstream>

/*
 * name: Gerp
 * purpose: default constructor 
 * arguments: driectory and output file 
 * returns: none
 * effects: creates instance of the gerp class to be used on a certain directory
 */
Gerp::Gerp(string directory, string outputFilename) {
    this->directory = directory;
    outputFile.open(outputFilename);
}

Gerp::~Gerp() {
    for (int i = 0; i < lines.size(); i++) {
        delete lines[i];
    }
}

/*
 * name: run
 * purpose: start the command loop responsible for querying the index
 * arguments: none
 * returns: none
 * effects: writes query results to output file
 */
void Gerp::run()
{
    buildIndex(directory);
    string command;
    cout << "Query? ";
    cin >> command;

    while(not(command == "@q" or command == "@quit" or cin.eof())){

        if (command == "@i" or command == "@insensitive") {
            string word;
            cin >> word;
            insensitiveAnyString(word);

        } else if (command == "@f") {
            string filename;
            cin >> filename;
            changeOutputFile(filename);
        } else {
            // it has to be a word
            anyString(command);
        }

        cout << "Query? ";
        cin >> command;
    }

    cout << "Goodbye! Thank you and have a nice day." << endl; 
}

/*
 * name: anyString
 * purpose: handles case sensitive word queries from the command loop
 * arguments: the word to query
 * returns: none
 * effects: writes result of query to output file
 */

void Gerp::anyString(string word) {
    string stripped = stripNonAlphaNum(word);
    vector<Line*> *raw_lines = raw_map.get(stripped);
    if(raw_lines != nullptr) {

        for (int i = 0; i < raw_lines->size(); i++)
        {
            Line *line = raw_lines->at(i);
            outputFile << line->filepath << ":" << line->line_number
                 << ": " << line->line << endl;
        }
    } else {
        outputFile << stripped << " Not Found. Try with @insensitive"
            << " or @i.\n";
    }
}

/*
 * name: insensitiveAnyString
 * purpose: Sort through the word insatcnes and find specific case sensitive 
 * word
 * arguments: string words                
 * returns: none
 * effects: finds the case sensitive word 
 */
void Gerp::insensitiveAnyString(string word) {
    string stripped = stripNonAlphaNum(word);
    string lowercase = toLowerCase(stripped);
    vector<Line*> *std_lines = std_map.get(lowercase);
    if (std_lines != nullptr) {
        for (int i = 0; i < std_lines->size(); i++)
        {
            Line *line = std_lines->at(i);
            outputFile << line->filepath << ":" << line->line_number
                 << ": " << line->line << endl;
        }
    } else {
        outputFile << stripped << " Not Found.\n";
    }
}

/*
 * name: changeOutputFile
 * purpose: change the output file
 * arguments: string newFilename
 * returns: none
 * effects: creates a new file
 */
void Gerp::changeOutputFile(string newFilename) {
    outputFile.close();
    outputFile.open(newFilename);

}

/*
 * name: buildIndex
 * purpose: build all the paths in the file
 * arguments: string directory
 * returns: none
 * effects: Adds all line numbers to a hash map
 */
void Gerp::buildIndex(string directory) {
    FSTree tree(directory);
    recurseDir(tree.getRoot(), "");
}

/*
 * name: recursiveDir
 * purpose: recursive helper to get all files
 * arguments: DirNode *n, string path
 * returns: none
 * effects: Adds all line numbers to a hash map
 */
void Gerp::recurseDir(DirNode *n, string path) {

    path = path + n->getName() + "/";

    for (int i = 0; i < n->numFiles(); i++) {
        indexFile(path + n->getFile(i));
    }
    for (int i = 0; i < n->numSubDirs(); i++) {
        recurseDir(n->getSubDir(i), path);
    }
}

/*
 * name: indexFile
 * purpose: Read through the file and build key pairs for hash map
 * arguments: string path
 * returns: none
 * effects: populates hash map
 */
void Gerp::indexFile(string path) {
    ifstream file;
    file.open(path);
    if (not file.is_open()) {
        throw runtime_error("not open");
    }
    const int BUFFERSIZE = 131072;
    char buffer[BUFFERSIZE];
    while(not file.eof()) {

        file.read(buffer, BUFFERSIZE);
        int readSize = file.gcount();

        string line_string;
        string word_string;

        int line_count = 1;
        Line *curr_line = new Line;
        lines.push_back(curr_line);

        for (int i = 0; i < readSize; i++) {
            if (buffer[i] == ' ') 
            {
                string line_key = path + ":" + to_string(line_count);
                indexWord(word_string, curr_line);
                line_string += buffer[i];
                word_string = "";
            } 
            else if (buffer[i] == '\n')
            {
                curr_line->filepath = path;
                curr_line->line_number = line_count;
                curr_line->line = line_string;

                indexWord(word_string, curr_line);

                // reset everything for next line
                curr_line = new Line;
                lines.push_back(curr_line);

                line_string = "";
                word_string = "";
                line_count++;
            } else {
                line_string += buffer[i];
                word_string += buffer[i];
            }
        }
        if (line_string.size() != 0 )
        {
            curr_line->filepath = path;
            curr_line->line_number = line_count;
            curr_line->line = line_string;

            indexWord(word_string, curr_line);
        }
    }
    file.close();
}

/*
 * name: indexWord
 * purpose: build map of each individual word
 * arguments: string line, string key
 * returns: void
 * effects: builds hash map of all case insensitive
 */
void Gerp::indexWord(const string &word, Line *line)
{
  

    string processed_word = stripNonAlphaNum(word);
    string lowercase_word = toLowerCase(processed_word);

    raw_map.insert(processed_word, line);
    std_map.insert(lowercase_word, line);
}