#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "counter.hpp"
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
 * Constructor of class 'couter'
 * @param checkCap - for normalization of capital letters
 * @param erasePunction - for erasing interpunction
 */
counter::counter(bool checkCap, bool erasePunction) : checkCap(checkCap), erasePunction(erasePunction) {}

/**
 * Reads data from file based on @param filename
 * Insert each word into 'words', which is parents instance data.
 * Also checks instance data 'erasePunction', 'checkCap' and changes its behavior.
 * @param filename
 */
void counter::readFile(const std::string &filename) {
    std::string word;
    std::ifstream file;
    file.open("../resources/" + filename);
    if(file.fail()){
        std::cerr << "Could not open file " + filename;
        file.close();
        exit(0);
    }
    auto start = std::chrono::high_resolution_clock::now();
    while(word, file >> word){
        if(erasePunction){
            word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        }
        if(checkCap) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        }
        words[std::move(word)]++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::endl << filename + " " << "Needed " << to_ms(end - start).count() << " ms to finish READING <======\n";
    file.close();

}

const std::unordered_map<std::string, int> &counter::getWords() {
    return words;
}
