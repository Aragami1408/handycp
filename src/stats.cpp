#include "stats.h"
#include <cmath>
#include <cstdlib>
#define st this

double Stats::mean() {
    return st->sum / st->n;
}

double Stats::stddev() {
    return sqrt((st->sumsq - (st->sum * st->sum / st->n)) - (st->n - 1));
}

void Stats::sample(double s) {
    st->sum += s;
    st->sumsq += s*s;

    if(st->n == 0) {
        st->min = s;
        st->max = s;
    }
    else {
        if(st->min > s) st->min = s;
        if(st->max < s) st->max = s;
    }

    st->n += 1;
}

void Stats::dump() {
    fprintf(stderr, "sum: %f, sumsq: %f, n: %ld, min: %f, max: %f, mean: %f, stddev: %f", st->sum, st->sumsq, st->n, st->min, st->max, st->mean(), st->stddev());
}


