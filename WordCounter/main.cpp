#include <iostream>
#include <chrono>
#include <vector>
#include "sequence.hpp"
#include "parallel.hpp"
#include <thread>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <unordered_map>
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
 * Save instance data 'words' into file created based on @param filename.
 * @param filename
 */
void saveWords(const std::string& filename, const std::unordered_map<std::string, int>& words) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string outputName = "counted_"+filename;
    std::ofstream file("../resources/counted/" + outputName);
    if(file.fail()){
        std::cerr << "Error while creating new file..";
        exit(0);
    }
    auto it = words.begin();
    file << "Word"<<std::setw(16) <<  "Count" << "\r\n";
    file << "--------------------" <<  "\r\n";
    while(it != words.end()){
        file << it->first << std::setw((int) (20 - it->first.length())) << it->second << "\r\n" ;
        ++it;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\r\n" << "Needed " << to_ms(end - start).count() << " ms to SAVE <======\n";
}

/**
 * Prints help to console if users terminal input was '--help'
 */
void printHelp(){
    std::cout << "-st/-mt -c -i file1 file2 ... filex\r\n";
    std::cout << "-----------------------------------\r\n";
    std::cout << "-st ... single-thread\r\n";
    std::cout << "-mt ... multi-thread\r\n";
    std::cout << "-----------------------------------\r\n";
    std::cout << "-c ... detect capital letters --- e.g. Dog != dog\r\n";
    std::cout << "-----------------------------------\r\n";
    std::cout << "-i do not erase interpunction\r\n";
    std::cout << "-----------------------------------\r\n";
}

/**
 * Creates instance of class parallel and starts reading a file.
 * @param erasePunction
 * @param checkCap
 * @param filename
 */
void threadInstance(parallel& instance){
    instance.read();
}

/**
 * Function for parallelization. Takes number of user inputs @param argc, user inputs @param argv.
 * Based on that does some input validation and for each file creates thread that runs 'theadInstance' method
 * @param argc
 * @param argv
 */
void runParallel(const bool& checkCap, const bool& erasePunction, const std::vector<std::string>& files){
    std::vector<parallel> instances;
    for(auto it = files.begin(); it != files.end(); ++it){
        instances.push_back( parallel(checkCap, erasePunction, *it) );
    }
    std::vector<std::thread> threads;

    for(auto it = instances.begin(); it != instances.end(); ++it){
        threads.push_back(std::thread(threadInstance, std::ref(*it)));
    }

    for(auto it = threads.begin(); it != threads.end(); ++it){
        it->join();
    }
    std::unordered_map<std::string, int> finalMap;
    for(auto it = instances.begin(); it != instances.end(); ++it){
        for(std::pair<std::string, int> pair : it->getWords()){
            finalMap[std::move(pair.first)] += pair.second;
        }
    }
    saveWords("parallel.txt", finalMap);

}
/**
 * Function for sequential run. Takes number of user inputs @param argc, user inputs @param argv.
 * Based on that does some validaton and reads input files one by one.
 * @param argc
 * @param argv
 */
void runSequence(const bool& checkCap, const bool& erasePunction, const std::vector<std::string>& files){
    sequence seq(checkCap,erasePunction,files);
    seq.read();
    saveWords("sequence.txt", seq.getWords());
}

/**
 * Based on user input parameters fill parameters pased by
 * reference (@param checkCap @param erasePunction @param threads @param files) and validate.
 * @param argc
 * @param argv
 * @param checkCap
 * @param erasePunction
 * @param threads
 * @param files
 * @return
 */
bool checkUserInput(int& argc, char* argv[], bool& checkCap, bool& erasePunction, bool& threads, std::vector<std::string>& files){
    if(argc <= 1) return false;
    for(int i = 1 ; i < argc; i++) {
        if (std::string(argv[i]) == "-mt" || std::string(argv[i]) == "-st") threads = std::string(argv[i]) == "-mt";
        else if (std::string(argv[i]) == "-c") checkCap = true;
        else if (std::string(argv[i]) == "-i") erasePunction = true;
        else if (std::string(argv[i]) == "--help") {
            printHelp();
            return false;
        } else if (std::string(argv[i]).find(".txt") != std::string::npos){
            std::cout << "Program is about to work with file: " << std::string(argv[i]) <<"\r\n";
            files.push_back(std::string(argv[i]));
        } else {
            std::cerr << "Wrong input: " << std::string(argv[i]) << "\r\n" << "Use --help for advice";
            return false;
        }
    }
    return true;
}

/**
 * Main function of program.
 * Terminal paramenters have to be in format: [ -st/-mt -f/-o -i/-ei file1.txt file2.txt ... filex.txt  ]
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    bool erasePunction = false;
    bool checkCap = false;
    bool threads = false;
    std::vector<std::string> files;

    if(checkUserInput(argc, argv, checkCap, erasePunction, threads, files) && files.size() > 0){
        if(threads) {
            std::cout << "\r\nStarting MULTI-thread run..." << "\r\n";
            runParallel(checkCap, erasePunction, files);
        } else {
            std::cout << "\r\nStarting SINGLE-thread run..." << "\r\n";
            runSequence(checkCap, erasePunction, files);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::endl << "Needed " << to_ms(end - start).count() << " ms to finish WHOLE PROGRAM <======\n";
}


