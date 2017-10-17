
#ifndef WORDCOUNTER_SEQUENCE_HPP
#define WORDCOUNTER_SEQUENCE_HPP

#include <map>
#include <vector>
#include "string"
#include "counter.hpp"

class sequence : public counter {
public:
    sequence(bool checkCap, bool erasePunction, const std::vector<std::string> &files);
    virtual void read() override ;
private:
    std::vector<std::string> files;
};
#endif //WORDCOUNTER_SEQUENCE_HPP
