#pragma once
#include <vector>
class Stats {
public:

    Stats(double sum, double sumsq, unsigned long n, double min, double max): 
        sum(sum), 
        sumsq(sumsq), 
        n(n), 
        min(min), 
        max(max){}
    Stats(): 
        sum(0.0), 
        sumsq(0.0), 
        n(0L), 
        min(0.0), 
        max(0.0) {}
    double mean();
    double stddev();
    void sample(double s);
    void dump();
private:
    double sum;
    double sumsq;
    unsigned long n;
    double min;
    double max;

};
