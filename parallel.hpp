
#ifndef WORDCOUNTER_PARALLEL_HPP
#define WORDCOUNTER_PARALLEL_HPP
#include "counter.hpp"
class parallel : public counter {
public:
    parallel(bool checkCap, bool erasePunction, const std::string &filename);
    virtual void read() override ;
private:
    std::string filename;

};
#endif //WORDCOUNTER_PARALLEL_HPP