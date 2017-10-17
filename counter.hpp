
#ifndef WORDCOUNTER_COUNTER_HPP
#define WORDCOUNTER_COUNTER_HPP
#include <string>
#include <map>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <mutex>

class counter {
public:
    std::unordered_map<std::string, int> words;
    counter(bool checkCap, bool erasePunction);
    virtual void readFile(const std::string& filename);
    virtual void read()= 0;
    const std::unordered_map<std::string, int> &getWords();

protected:
    bool checkCap;
    bool erasePunction;
};
#endif //WORDCOUNTER_COUNTER_HPP