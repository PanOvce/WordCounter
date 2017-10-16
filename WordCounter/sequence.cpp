#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "sequence.hpp"

/**
 * Read method for sequence classl
 * Iterate over vector of filenames and call readFile method with each filename
 * Each input file is then saved into output file.
 */
void sequence::read() {
    std::vector<std::string>::iterator it = files.begin();
    while(it != files.end()){
        readFile(*it);
        ++it;
    }
}

/**
 * Constructor for class 'sequence'.
 * Calls parent constructor for @param checkCap and @param erasePunction.
 * Saves @param files into its own instance data std::vector 'files'
 * @param checkCap
 * @param erasePunction
 * @param files - Vector of files im about to read
 */
sequence::sequence(bool checkCap, bool erasePunction, const std::vector<std::string> &files) : counter(checkCap,
                                                                                                       erasePunction),
                                                                                               files(files) {}
