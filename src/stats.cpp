/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Statistics Engine
 *
 *
 * Copyright © 2021 Aragami1408/D6E093 <vucaominh1408@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stats.h>
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


