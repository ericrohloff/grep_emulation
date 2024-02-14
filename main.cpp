/*
 * main.cpp
 * Abe Nelson (anelso18) and Eric Rohloff (erohlo01)
 * 12/03/2023
 *
 * COMP 15 Project: gerp
 *
 * main.cpp
 * The entrypoint the gerp command line tool. Initializes the Gerp class and
 * handles incorrect commandline usage.
 *
 */

#include "Gerp.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;

        exit(EXIT_FAILURE);
    }
    Gerp instance(argv[1], argv[2]);
    instance.run();
}