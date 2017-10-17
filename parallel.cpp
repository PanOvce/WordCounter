#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "parallel.hpp"
//TIME MEASSUREMENT IN THIS FILE IS JUST FOR DEVELOPMENT.
/**
 * Time meassurement method. Returns current time in milliseconds when called.
 * @tparam TimePoint
 * @param tp
 * @return
 */
template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}
/**
 * Read method for parallel class.
 * Calls readFile method with filename instance data
 */
void parallel::read() {
    readFile(filename);
}

/**
 * Constructor for class 'parallel'.
 * Calls parent constructor for @param checkCap and @param erasePunction.
 * Saves @param fileName into its own instance data std::string 'filename'.
 * @param checkCap
 * @param erasePunction
 * @param fileName - Name of the file im about to read
 */
parallel::parallel(bool checkCap, bool erasePunction, const std::string &filename) : counter(checkCap, erasePunction),
                                                                                     filename(filename) {}


